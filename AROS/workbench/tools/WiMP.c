/*
    (C) 1995-2000 AROS - The Amiga Research OS
    $Id$

    Desc: Window Manipulation Program
    Lang: english
*/

/*****************************************************************************

    NAME

        WiMP

    SYNOPSIS

    LOCATION

        Workbench:Tools

    BUGS

    SEE ALSO

    INTERNALS

    HISTORY

        11-Dec-2000     hkiel     Initial version

******************************************************************************/

static const char version[] = "$VER: WiMP 0.1 (12.12.2000)\n";

#define AROS_ALMOST_COMPATIBLE

#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <devices/keymap.h>
#include <dos/dos.h>
#include <dos/exall.h>
#include <dos/datetime.h>
#include <exec/lists.h>
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/tasks.h>
#include <exec/execbase.h>
#include <graphics/gfxbase.h>
#include <graphics/gfx.h>
#include <graphics/rastport.h>
#include <graphics/gfxmacros.h>
#include <intuition/intuitionbase.h>
#include <intuition/intuition.h>
#include <intuition/classusr.h>
#include <intuition/gadgetclass.h>
#include <intuition/imageclass.h>
#include <proto/alib.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/aros.h>
#include <proto/utility.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/console.h>
#include <aros/machine.h>
#include <proto/gadtools.h>
#include <libraries/gadtools.h>

struct IntuitionBase *IntuitionBase;
struct Library *GadToolsBase;
struct GfxBase *GfxBase;
struct Screen *Screen;
struct Window *Window;


enum {None_type,Window_type,Screen_type,Max_type};

#define ID_ZIP 12
struct NewGadget zipgad =
{
    479, 130, 30, 20,
    "Zip", NULL,
    ID_ZIP, PLACETEXT_IN, NULL, NULL
};

#define ID_ACTIVATE 13
struct NewGadget activategad =
{
    409, 130, 70, 20,
    "Activate", NULL,
    ID_ACTIVATE, PLACETEXT_IN, NULL, NULL
};

#define ID_ORIGIN 14
struct NewGadget origingad =
{
    289, 130, 120, 20,
    "Move To Origin", NULL,
    ID_ORIGIN, PLACETEXT_IN, NULL, NULL
};

#define ID_BACK 15
struct NewGadget backgad =
{
    220, 130, 69, 20,
    "To Back", NULL,
    ID_BACK, PLACETEXT_IN, NULL, NULL
};

#define ID_FRONT 16
struct NewGadget frontgad =
{
    150, 130, 70, 20,
    "To Front", NULL,
    ID_FRONT, PLACETEXT_IN, NULL, NULL
};

#define ID_KILL 17
struct NewGadget killgad =
{
    110, 130, 40, 20,
    "Kill", NULL,
    ID_KILL, PLACETEXT_IN, NULL, NULL
};

#define ID_RESCUE 18
struct NewGadget rescuegad =
{
    10, 150, 130, 20,
    "Rescue Windows", NULL,
    ID_RESCUE, PLACETEXT_IN, NULL, NULL
};

#define ID_UPDATE 19
struct NewGadget updategad =
{
    10, 130, 100, 20,
    "Update List", NULL,
    ID_UPDATE, PLACETEXT_IN, NULL, NULL
};

#define ID_LISTVIEW 20
struct NewGadget listviewgad =
{
    10, 30, 500, 100,
    "Screen/Window List", NULL,
    ID_LISTVIEW, PLACETEXT_ABOVE, NULL, NULL
};

#define NUMLVNODES  3
struct List lv_list;
STRPTR lv_texts[] = {"Blah","blah","blubb"};
APTR vi;
struct Gadget *glist = NULL;
struct Gadget *screenlistg = NULL;

struct IntuiText killscr_body = {1,0,JAM1,10,10,NULL,(UBYTE *)"Do you really want to Close the selected Screen?",NULL};
struct IntuiText killwin_body = {1,0,JAM1,10,10,NULL,(UBYTE *)"Do you really want to Close the selected Window?",NULL};
struct IntuiText pos_body = {1,0,JAM1,10,10,NULL,(UBYTE *)"Yes.",NULL};
struct IntuiText neg_body = {1,0,JAM1,10,10,NULL,(UBYTE *)"No!",NULL};

VOID initlvnodes(struct List *list)
{
struct Screen *scr;
struct Window *win;
struct Node *node;
char tmp[1024];
char *string;

  NewList(list);

  scr = IntuitionBase->FirstScreen;
  while( scr )
  {
    sprintf(tmp,"Screen:   %p %4dx%4d @%4d.%4d \"%s\",\"%s\"",scr,scr->Width,scr->Height,scr->LeftEdge,scr->TopEdge,scr->Title,scr->DefaultTitle);
    string = strdup(tmp);
    node = (struct Node *) AllocMem ( sizeof(struct Node), MEMF_CLEAR );
    AddTail(list, node);
    SetNodeName(node, string);
    win = scr->FirstWindow;
    while( win )
    {
      sprintf(tmp,"  Window: %p %4dx%4d @%4d,%4d \"%s\"",win,win->Width,win->Height,win->LeftEdge,win->TopEdge,win->Title);
      string = strdup(tmp);
      node = (struct Node *) AllocMem ( sizeof(struct Node), MEMF_CLEAR );
      AddTail(list, node);
      SetNodeName(node, string);
      win = win->NextWindow;
    }
    scr = scr->NextScreen;
  }

return;
}

VOID freelvnodes(struct List *list)
{
struct Node *popnode;

  while ( ! IsListEmpty(list) )
  {
    popnode = RemTail(list);

    free (popnode->ln_Name);
    FreeMem ( popnode, sizeof(struct Node) );
  }
}

struct Gadget *gt_init()
{
    struct Gadget *gad = NULL;
    
    Screen = LockPubScreen(NULL);
    vi = GetVisualInfoA(Screen, NULL);
    if (vi != NULL)
	gad = CreateContext(&glist);
	
    return gad;
}

struct Gadget *makegadgets(struct Gadget *gad)
{
    listviewgad.ng_VisualInfo = vi;
    updategad.ng_VisualInfo = vi;
    rescuegad.ng_VisualInfo = vi;
    killgad.ng_VisualInfo = vi;
    frontgad.ng_VisualInfo = vi;
    backgad.ng_VisualInfo = vi;
    origingad.ng_VisualInfo = vi;
    activategad.ng_VisualInfo = vi;
    zipgad.ng_VisualInfo = vi;
    
    initlvnodes(&lv_list);
    gad = CreateGadget(LISTVIEW_KIND, gad, &listviewgad,
    		GTLV_Labels,	(IPTR)&lv_list,
    		GTLV_ReadOnly,	FALSE,
		TAG_DONE);
    screenlistg = gad;

    gad = CreateGadget(BUTTON_KIND, gad, &updategad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &rescuegad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &killgad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &frontgad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &backgad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &origingad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &activategad,
		TAG_DONE);

    gad = CreateGadget(BUTTON_KIND, gad, &zipgad,
		TAG_DONE);

    if (!gad) {
        FreeGadgets(glist);
        printf("GTDemo: Error creating gadgets\n");
    }
    return gad;
}

void open_lib()
{
  IntuitionBase = (struct IntuitionBase *) OpenLibrary("intuition.library",0L);
  GfxBase = (struct GfxBase *) OpenLibrary("graphics.library",0L);
  GadToolsBase = OpenLibrary("gadtools.library",0L);
}

void open_window()
{
  Window = OpenWindowTags ( NULL
	, WA_Title,	    "WiMP"
	, WA_Left,	    0
	, WA_Top,	    0
	, WA_Width,	    520
	, WA_Height,	    180
	, WA_IDCMP,	    IDCMP_REFRESHWINDOW
			    | IDCMP_MOUSEBUTTONS
			    | IDCMP_GADGETUP
			    | IDCMP_CLOSEWINDOW
	, WA_Flags,	    WFLG_DRAGBAR
			    | WFLG_DEPTHGADGET
			    | WFLG_CLOSEGADGET
			    | WFLG_NOCAREREFRESH
			    | WFLG_SMART_REFRESH
			    | WFLG_ACTIVATE
	, WA_SimpleRefresh, TRUE
	, TAG_END
    );
}

void close_window()
{
  CloseWindow(Window);
  FreeGadgets(glist);
  FreeVisualInfo(vi);
  UnlockPubScreen(NULL, Screen);
}

void close_lib()
{
  CloseLibrary((struct Library *)IntuitionBase);
  CloseLibrary((struct Library *)GfxBase);
  CloseLibrary(GadToolsBase);
}

IPTR getsw(int *type)
{
IPTR gadget;
IPTR xptr;

  GT_GetGadgetAttrs(screenlistg,Window,NULL,
      GTLV_Selected, (IPTR)&gadget,
      TAG_DONE);
  if( gadget != -1)
  {
  struct Node *xnode;
  char *xnodename;

    xnode = (struct Node *)GetHead(&lv_list);
    for(;gadget>0;gadget--)
    {
      xnode = GetSucc(xnode);
    }
    xnodename = GetNodeName(xnode);
    switch(xnodename[2])
    {
      case 'r' : /* "Screen:" */
	  *type = Screen_type;
	  xptr = (IPTR)strtol(&(xnodename[12]),NULL,16);
	  break;
      case 'W' : /* "  Window:" */
	  *type = Window_type;
	  xptr = (IPTR)strtol(&(xnodename[12]),NULL,16);
	  break;
      default:
	  break;
    }
    return xptr;
  }
  else
  {
    *type = None_type;
    return 0;
  }
}

VOID update_list()
{
  freelvnodes(&lv_list);
  initlvnodes(&lv_list);
  GT_SetGadgetAttrs(screenlistg,Window,NULL,
      GTLV_Labels, (IPTR)&lv_list,
      GTLV_Selected, (IPTR)-1,
      TAG_DONE);
  GT_RefreshWindow(Window,NULL);
}

int main()
{
struct Screen *scr;
struct Window *win;
struct Gadget *gad;
struct IntuiMessage *msg;
ULONG class;
UWORD code;
IPTR object;
int type;
int quit=0;

  open_lib();
  open_window();

  gad = gt_init();
  gad = makegadgets(gad);
  AddGList(Window,glist,0,-1,NULL);
  RefreshGList(glist,Window,NULL,-1);

  while(quit==0)
  {
    WaitPort(Window->UserPort);
    msg=(struct IntuiMessage *)GetMsg(Window->UserPort);
    class=msg->Class;
    switch(class)
    {
      case IDCMP_CLOSEWINDOW :
		quit=1;
		break;

      case IDCMP_GADGETUP :
		switch (((struct Gadget *) msg->IAddress)->GadgetID)
		{
		  case ID_UPDATE:
			update_list();
			break;

		  case ID_ZIP:
			object = getsw(&type);
			if(type==Window_type)
			{
			  ZipWindow((struct Window *)object);
			}
			update_list();
			break;

		  case ID_ACTIVATE:
			object = getsw(&type);
			if(type==Window_type)
			{
			  ActivateWindow((struct Window *)object);
			}
			update_list();
			break;

		  case ID_FRONT:
			object = getsw(&type);
			if(type==Screen_type || type==Window_type)
			{
			  switch(type)
			  {
			    case Screen_type :
				ScreenToFront((struct Screen *)object);
				break;
			    case Window_type :
				WindowToFront((struct Window *)object);
				break;
			    default:
				break;
			  }
			}
			update_list();
			break;

		  case ID_BACK:
			object = getsw(&type);
			if(type==Screen_type || type==Window_type)
			{
			  switch(type)
			  {
			    case Screen_type :
				ScreenToBack((struct Screen *)object);
				break;
			    case Window_type :
				WindowToBack((struct Window *)object);
				break;
			    default:
				break;
			  }
			}
			update_list();
			break;

		  case ID_ORIGIN:
			object = getsw(&type);
			if(type==Screen_type || type==Window_type)
			{
			  switch(type)
			  {
			    case Screen_type :
				MoveScreen((struct Screen *)object,-((struct Screen *)object)->LeftEdge,-((struct Screen *)object)->TopEdge);
				break;
			    case Window_type :
				MoveWindow((struct Window *)object,-((struct Window *)object)->LeftEdge,-((struct Window *)object)->TopEdge);
				break;
			    default:
				break;
			  }
			  Delay(5);
			}
			update_list();
			break;

		  case ID_KILL:
			object = getsw(&type);
			if(type==Screen_type || type==Window_type)
			{
			int killit;
			  switch(type)
			  {
			    case Screen_type :
				killit = AutoRequest(Window,&killscr_body,&pos_body,&neg_body,0,0,200,75);
				if( killit == TRUE )
				{
				  CloseScreen((struct Screen *)object);
				}
				break;
			    case Window_type :
				killit = AutoRequest(Window,&killwin_body,&pos_body,&neg_body,0,0,200,75);
				if( killit == TRUE )
				{
				  CloseWindow((struct Window *)object);
				}
				break;
			    default:
				break;
			  }
			}
			update_list();
			break;

		  case ID_RESCUE:
			scr = IntuitionBase->FirstScreen;
			while( scr )
			{
			  win = scr->FirstWindow;
			  while( win )
			  {
			    if(    win->LeftEdge < 0
				|| win->TopEdge  < 0
				|| win->LeftEdge > scr->Width
				|| win->TopEdge  > scr->Height )
			    {
			      MoveWindow ( win, - win->LeftEdge, - win->TopEdge );
			    }
			    win = win->NextWindow;
			  }
			  scr = scr->NextScreen;
			}

			Delay(5);
			update_list();
			break;

		  case ID_LISTVIEW:
			break;

		  default:
			break;
		}
		break;

        default :
		break;
    }
    ReplyMsg((struct Message *)msg);
  }

  close_window();
  close_lib();
  return(0);
}

