/* 
  sorted_cleanup.plugin

  based on:

  Example source

        Name:           example_lib.c
		Versionstring:  $VER: example_lib.c 1.2 (21.06.2007)
        Author:         Jens Langner
        Distribution:   PD
        Description:    shows how the SDI_lib.h header include can be used

  1.0   05.10.04 : initial version showing how the SDI_lib.h headers can help
                   when used for maintaining AmigaOS compatible shared library
                   interfaces upon compatible operating systems like AmigaOS3,
                   AmigaOS4 and MorphOS.

  1.1   20.06.07 : moved LIBFUNC to be first in line acording to changes in
				   SDI_lib.h. (Guido Mersmann)

  1.2   21.06.07 : added missing libvector to MorphOS/AmigaOS3 libvectors[]
				   (Guido Mersmann)

  Please note that this example is just for educational purposes and wasn't
  checked for complete correctness. However, it should compile and probably also
  work as expected. But please note that its purpose is to show how a shared
  library can held platform independent over all different available AmigaOS
  platforms like OS3, OS4 and MorphOS.

  Feel free to comment and submit any suggestions directly to
  Jens.Langner@light-speed.de

*/

#include <exec/types.h>
#include <exec/libraries.h>
#include <exec/resident.h>
#include <dos/dos.h>
#include <workbench/workbench.h>

#include <proto/exec.h>

#ifdef __amigaos4__
#include <exec/emulation.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#include <SDI_lib.h>
#include <SDI_stdarg.h>
#include <SDI_hook.h>

#include "datatypes/iconobject.h"
#include "scalos/scalos.h"
#include "scalos/undo.h"

#define VERSION		41
#define REVISION	7
#define DATE		  "30.06.2014"
#define VERS		  "sorted_cleanup.plugin 41.7"
#define VSTRING		"sorted_cleanup.plugin 41.7 30.06.2014)\r\n"
#define VERSTAG		"\0$VER: sorted_cleanup.plugin 41.7 (30.06.2014)"

static const char UserLibName[] = "sorted_cleanup.plugin";
static const char UserLibID[]   = "\0$VER: sorted_cleanup.plugin 41.7 (30.06.2014)";

#if defined(__MORPHOS__)
struct ExecBase *SysBase;
#endif

/******************************************************************************/
/*             >> User defineable library functions start here <<             */
/*  The following section should illustrate how the SDI_lib.h macros make it  */
/*   possible to easily maintain a typical Amiga shared library interface if  */
/*      compatibility over all common (OS3/OS4, MorphOS) is required          */
/******************************************************************************/

// first the prototypes of all our public library functions
LIBPROTO(menufunction, void, REG(a0, struct WindowTask *wt), REG(a1, struct ScaIconNode *in));

// let us now create the libvector.
// Please note that the start of the vectors has to be always the "LFUNC_FAS"
// macro
#define libvector LFUNC_FAS(menufunction)

// then we require to generate library stubs for each library functions
// because OS4 comes with an additional "struct Interface*" parameter which we
// want to keep transparent in our code. Therefore we need to have wrapper/stub
// functions to call the real functions instead.
#if defined(__amigaos4__)

LIBPROTO(menufunction, void, REG(a0, struct WindowTask *wt), REG(a1, struct ScaIconNode *in))
{
	return menufunction(wt, in);
}

#endif

// Now the real implementations of the library functions above like in
// a normal AmigaOS shared library follow

HOOKPROTONHNO(RedoHook, UndoEvent *);
MakeHook(RedoHook, RedoFunc);

HOOKPROTONH(CompareNameHook, int, o, o2);
MakeHook(CompareNameHook, comparenamefunc);

LIBFUNC void menufunction(REG(a0, struct WindowTask *wt), REG(a1, struct ScaIconNode *in))
{
	DoMethod(wt->mt_MainObject, SCCM_IconWin_AddUndoEvent, UNDO_Cleanup, UNDOTAG_IconList,
	  wt->wt_IconList, UNDOTAG_WindowTask, wt, UNDOTAG_CleanupMode, CLEANUP_Default,
	  UNDOTAG_RedoHook, &RedoHook);
	menufunction2(wt);
}

menufucntion2(wt)
{
  Node *iter;
  
  ObtainSemaphore(wt->wt_IconSemaphore);
  iter=wt->wt_LateIconList;
  while (iter != NULL)
  {
    sca_MoveNode(&wt->wt_LateIconList, &wt->wt_IconList, iter);
    iter=iter->LN_SUCC;
  }
  wt->wt_LateIconList = wt->wt_IconList;
  wt_IconList = NULL;
  sca_SortNodes(&wt->wt_LateIconList, &CompareNameHook, SCA_SortType_Best);
  ReleaseSemaphore(wt->wt_IconSemaphore);
  wt->wt_XOffset = 0;
  wt->mt_WindowStruct->ws_xoffset = wt->wt_XOffset;
  DoMethod(wt->mt_MainObject, SCCM_IconWin_CleanUp);
  DoMethod(wt->mt_MainObject, SCCM_IconWin_SetVirtSize, SETVIRTF_AdjustRightSlider | SETVIRTF_AdjustBottomSlider);
  DoMethod(wt->mt_MainObject, SCCM_IconWin_Redraw, 0);
}

int comparenamefunc(scaIconNode *o, scaIconNode *o2)
{
  APTR a = NULL, b = NULL;
  if (IntuitionBase != NULL)
  {
    GetAttr(IDTA_Type, o2->in_Icon, &a);
    GetAttr(IDTA_Type, o->in_Icon, &b);
    if (b != WBDRAWER)
    {
      if (a == WBDRAWER)
      {
        /* greater */
        return 1;
      }
    }
    else
    {
      /* first drawer */
      if (a != WBDRAWER)
      {
        /* smaller */
        return -1;
      }
    }
    /* files */
    if ((a=o->in_Name) && (b=o2->in_Name))
    {
      return Stricmp(a,b);
    }
    return 1;
  }
}

IPTR RedoFunc(UndoEvent *ue)
{
  return InternalRedoFunc(ue->ucd_WindowTask.uev_Data, ue);
}

/******************************************************************************/
/*    Starting from here starts the "standard" Amiga library initialization.  */
/*  All the above should have illustrated enough how "easy" it is to use the  */
/*  SDI_lib.h header file and how it can help in developing a shared library  */
/*               for multiple AmigaOS compatible platforms.                   */
/******************************************************************************/

/******************************************************************************/
/* Local Structures & Prototypes                                              */
/******************************************************************************/

struct LibraryHeader
{
	struct Library	libBase;
	struct Library *sysBase;
	ULONG           segList;
	struct Library *scalosBase;
	struct Library *utilityBase;
	struct Library *intuitionBase;
#ifdef __amigaos4__
	struct ScalosIFace *IScalos;
	struct UtilityIFace *IUtility;
	struct IntuitionIFace *IIntuition;
#endif
};

#if defined(__amigaos4__)

LIBFUNC static struct LibraryHeader * LibInit    (struct LibraryHeader *base, BPTR librarySegment, struct ExecIFace *pIExec);
LIBFUNC static BPTR                   LibExpunge (struct LibraryManagerInterface *Self);
LIBFUNC static struct LibraryHeader * LibOpen    (struct LibraryManagerInterface *Self, ULONG version);
LIBFUNC static BPTR                   LibClose   (struct LibraryManagerInterface *Self);

#elif defined(__MORPHOS__)

LIBFUNC static struct LibraryHeader * LibInit   (struct LibraryHeader *base, BPTR librarySegment, struct ExecBase *sb);
LIBFUNC static BPTR                   LibExpunge(void);
LIBFUNC static struct LibraryHeader * LibOpen   (void);
LIBFUNC static BPTR                   LibClose  (void);
LIBFUNC static LONG                   LibNull   (void);

#else

LIBFUNC static struct LibraryHeader * LibInit    (REG(a0, BPTR Segment), REG(d0, struct LibraryHeader *lh), REG(a6, struct ExecBase *sb));
LIBFUNC static BPTR                   LibExpunge (REG(a6, struct LibraryHeader *base));
LIBFUNC static struct LibraryHeader * LibOpen    (REG(a6, struct LibraryHeader *base));
LIBFUNC static BPTR                   LibClose   (REG(a6, struct LibraryHeader *base));
LIBFUNC static LONG                   LibNull    (void);

#endif

/******************************************************************************/
/* Dummy entry point and LibNull() function all in one                        */
/******************************************************************************/

#if defined(__amigaos4__)
int _start(void)
#else
int Main(void)
#endif
{
  return RETURN_FAIL;
}

#if !defined(__amigaos4__)
LIBFUNC static LONG LibNull(VOID)
{
  return(0);
}
#endif

/******************************************************************************/
/* Local data structures                                                      */
/******************************************************************************/

#if defined(__amigaos4__)
/* ------------------- OS4 Manager Interface ------------------------ */
STATIC ULONG LibObtain(struct LibraryManagerInterface *Self)
{
  return(Self->Data.RefCount++);
}

STATIC ULONG LibRelease(struct LibraryManagerInterface *Self)
{
  return(Self->Data.RefCount--);
}

STATIC CONST APTR LibManagerVectors[] =
{
  (APTR)LibObtain,
  (APTR)LibRelease,
  (APTR)NULL,
  (APTR)NULL,
  (APTR)LibOpen,
  (APTR)LibClose,
  (APTR)LibExpunge,
  (APTR)NULL,
  (APTR)-1
};

STATIC CONST struct TagItem LibManagerTags[] =
{
  {MIT_Name,             (ULONG)"__library"},
  {MIT_VectorTable,      (ULONG)LibManagerVectors},
  {MIT_Version,          1},
  {TAG_DONE,             0}
};

/* ------------------- Library Interface(s) ------------------------ */

STATIC CONST APTR LibVectors[] =
{
   (APTR)LibObtain,
   (APTR)LibRelease,
	 (APTR)NULL,
	 (APTR)NULL,
	 (APTR)libvector,
   (APTR)-1
};

STATIC CONST struct TagItem MainTags[] =
{
   {MIT_Name,              (ULONG)"main"},
	 {MIT_VectorTable,       (ULONG)LibVectors},
   {MIT_Version,           1},
   {TAG_DONE,              0}
};


STATIC CONST ULONG LibInterfaces[] =
{
   (ULONG)LibManagerTags,
   (ULONG)MainTags,
   (ULONG)0
};

/* --------------------- m68k Library stubs ------------------------ */

STATIC ULONG stub_OpenPPC(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	return (ULONG) Self->Open(0);
}
struct EmuTrap stub_Open = { TRAPINST, TRAPTYPE, stub_OpenPPC };

STATIC ULONG stub_ClosePPC(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	return (ULONG) Self->Close();
}
struct EmuTrap stub_Close = { TRAPINST, TRAPTYPE, stub_ClosePPC };

STATIC ULONG stub_ExpungePPC(ULONG *regarray)
{
	return 0UL;
}
struct EmuTrap stub_Expunge = { TRAPINST, TRAPTYPE, stub_ExpungePPC };

STATIC ULONG stub_ReservedPPC(ULONG *regarray)
{
	return 0UL;
}
struct EmuTrap stub_Reserved = { TRAPINST, TRAPTYPE, stub_ReservedPPC };

STATIC ULONG VecTable68K[] =
{
	(ULONG)&stub_Open,
	(ULONG)&stub_Close,
	(ULONG)&stub_Expunge,
	(ULONG)&stub_Reserved,
	(ULONG)-1
};

/* ----------------------- LibCreate Tags -------------------------- */

STATIC CONST struct TagItem LibCreateTags[] =
{
   {CLT_DataSize,   (ULONG)(sizeof(struct LibraryHeader))},
   {CLT_InitFunc,   (ULONG)LibInit},
   {CLT_Interfaces, (ULONG)LibInterfaces},
   {CLT_Vector68K,  (ULONG)VecTable68K},
   {TAG_DONE,       0}
};

#else

STATIC CONST APTR LibVectors[] =
{
	#ifdef __MORPHOS__
	(APTR)FUNCARRAY_32BIT_NATIVE,
	#endif
  (APTR)LibOpen,
  (APTR)LibClose,
  (APTR)LibExpunge,
  (APTR)LibNull,
  (APTR)libvector,
  (APTR)-1
};

STATIC CONST ULONG LibInitTab[] =
{
	sizeof(struct LibraryHeader),
	(ULONG)LibVectors,
	(ULONG)NULL,
	(ULONG)LibInit
};

#endif

/* ------------------- ROM Tag ------------------------ */
static const USED_VAR struct Resident ROMTag =
{
  RTC_MATCHWORD,
  (struct Resident *)&ROMTag,
  (struct Resident *)&ROMTag + 1,
  #if defined(__amigaos4__)
  RTF_AUTOINIT|RTF_NATIVE,      // The Library should be set up according to the given table.
	#elif defined(__MORPHOS__)
	RTF_AUTOINIT|RTF_PPC,
  #else
  RTF_AUTOINIT,
  #endif
  VERSION,
  NT_LIBRARY,
  0,
  (APTR)UserLibName,
  VSTRING,
  #if defined(__amigaos4__)
  (APTR)LibCreateTags           // This table is for initializing the Library.
  #else
  (APTR)LibInitTab
  #endif
};

#if defined(__MORPHOS__)
/*
 * To tell the loader that this is a new emulppc elf and not
 * one for the ppc.library.
 * ** IMPORTANT **
 */
ULONG	USED_VAR __amigappc__=1;
ULONG	USED_VAR __abox__=1;

#endif /* __MORPHOS */

/******************************************************************************/
/* Standard Library Functions, all of them are called in Forbid() state.      */
/******************************************************************************/

#ifndef __amigaos4__
#define DeleteLibrary(LIB) \
  FreeMem((STRPTR)(LIB)-(LIB)->lib_NegSize, (ULONG)((LIB)->lib_NegSize+(LIB)->lib_PosSize))
#endif

#if defined(__amigaos4__)
static struct LibraryHeader * LibInit(struct LibraryHeader *base, BPTR librarySegment, struct ExecIFace *pIExec)
{
  struct ExecBase *sb = (struct ExecBase *)pIExec->Data.LibBase;
  IExec = pIExec;
#elif defined(__MORPHOS__)
static struct LibraryHeader * LibInit(struct LibraryHeader *base, BPTR librarySegment, struct ExecBase *sb)
{
#else
LIBFUNC static struct LibraryHeader * LibInit(REG(a0, BPTR librarySegment), REG(d0, struct LibraryHeader *base), REG(a6, struct ExecBase *sb))
{
#endif

  SysBase = (APTR)sb;

  base->libBase.lib_Node.ln_Type = NT_LIBRARY;
  base->libBase.lib_Node.ln_Pri  = 0;
  base->libBase.lib_Node.ln_Name = (char *)UserLibName;
  base->libBase.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  base->libBase.lib_Version      = VERSION;
  base->libBase.lib_Revision     = REVISION;
  base->libBase.lib_IdString     = (char *)UserLibID;

  base->segList = librarySegment;
  base->sysBase = (APTR)SysBase;

/* added library loading here -sc */
  base->scalosBase = OpenLibrary("scalos.library", 39L);
  base->utilityBase = OpenLibrary("utility.library", 39L);
  base->intuitionBase = OpenLibrary("intuition.library", 39L);
  
#ifdef __amigaos4__
  base->IScalos = GetInterface("main", 1L, NULL);
  base->IUtility = GetInterface("main", 1L, NULL);
  base->IIntuition = GetInterface("main", 1L, NULL);
#endif
  
  return(base);
}

#if defined(__amigaos4__)
static BPTR LibExpunge(struct LibraryManagerInterface *Self)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif defined(__MORPHOS__)
static BPTR LibExpunge(void)
{
	struct LibraryHeader *base = (struct LibraryHeader*)REG_A6;
#else
LIBFUNC static BPTR LibExpunge(REG(a6, struct LibraryHeader *base))
{
#endif
  BPTR rc;

  if(base->libBase.lib_OpenCnt > 0)
  {
    base->libBase.lib_Flags |= LIBF_DELEXP;
    return(0);
  }

  SysBase = (APTR)base->sysBase;
  rc = base->segList;

  Remove((struct Node *)base);
  
  /* inserted library closers here -sc */
#ifdef __amigaos4__
  DropInterface(IIntuition);
  DropInterface(IUtility);
  DropInterface(IScalos);
#endif
  CloseLibrary(intuitionBase);
  CloseLibrary(utilityBase);
  CloseLibrary(scalosBase);
  
  DeleteLibrary(&base->libBase);

  return(rc);
}

#if defined(__amigaos4__)
static struct LibraryHeader *LibOpen(struct LibraryManagerInterface *Self, ULONG version)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif defined(__MORPHOS__)
static struct LibraryHeader *LibOpen(void)
{
  struct LibraryHeader *base = (struct LibraryHeader*)REG_A6;
#else
LIBFUNC static struct LibraryHeader * LibOpen(REG(a6, struct LibraryHeader *base))
{
#endif
	
  base->libBase.lib_Flags &= ~LIBF_DELEXP;
	base->libBase.lib_OpenCnt++;

	return base;
}

#if defined(__amigaos4__)
static BPTR LibClose(struct LibraryManagerInterface *Self)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif defined(__MORPHOS__)
static BPTR LibClose(void)
{
	struct LibraryHeader *base = (struct LibraryHeader *)REG_A6;
#else
LIBFUNC static BPTR LibClose(REG(a6, struct LibraryHeader *base))
{	
#endif
	
  if(base->libBase.lib_OpenCnt > 0 &&
     --base->libBase.lib_OpenCnt == 0)
	{
		if(base->libBase.lib_Flags & LIBF_DELEXP)
    {
      #if defined(__amigaos4__)
      return LibExpunge(Self);
      #elif defined(__MORPHOS__)
      return LibExpunge();
      #else
      return LibExpunge(base);
      #endif
    }
	}	

	return 0;
}
