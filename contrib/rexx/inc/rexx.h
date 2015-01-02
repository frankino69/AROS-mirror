/*
 * $Header$
 * $Log$
 * Revision 1.2  2001/08/27 18:05:53  falemagn
 * removed ## from the definition of VERSION because it's unneeded and would make gcc-3.0 fail the compilation
 *
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.5  2000/04/07 07:17:10  bnv
 * Release 2.0.3
 *
 * Revision 1.4  1999/11/29 14:58:00  bnv
 * Changed: Some defines
 *
 * Revision 1.3  1999/05/14 13:08:00  bnv
 * Release 2.0.1
 *
 * Revision 1.2  1999/03/10 16:58:05  bnv
 * New release 2.0
 *
 * Revision 1.1  1998/07/02 17:35:50  bnv
 * Initial revision
 *
 */

/*
 *	Defined symbols in makefile
 *	__DEBUG__	enable debuging
 *	MSDOS		MSDOS compilation routines
 *	__BORLANDC__	to enable PORT,INTR,STORAGE()
 *	ALIGN		to enable DWORD align instead of byte
 *	INLINE		to inline some functions
 */
#ifndef __REXX_H_
#define __REXX_H_

#include <setjmp.h>

#include <lerror.h>
#include <lstring.h>

#include <dqueue.h>
#include <bintree.h>
#include <variable.h>

#ifdef  __REXX_C__
#	define EXTERN
#	ifdef __BORLANDC__
		extern unsigned _stklen = 32000U;
#	endif
#else
#	define EXTERN extern
#endif

/* ------------ some defines ------------------ */
#define	VERSION		"ARexx V0.5.0 " __DATE__
#define	AUTHOR		"Mario Cassani, from BRexx 2.0.3 by Vassilis N. Vlachoudis"
#define REGAPPKEY	TEXT("Software\\Marmita\\BRexx")
#define	SCIENTIFIC	0
#define ENGINEERING	1

#define MAXARGS		15
#define PROC_INC	10
#define CLAUSE_INC	100
#define CODE_INC	256
#define STCK_SIZE	255

/* call types */
#define CT_PROGRAM	0
#define CT_PROCEDURE	1
#define CT_FUNCTION	2
#define	CT_INTERPRET	3
#define CT_INTERACTIVE	4

/* signal on condition */
#define SC_ERROR	0x01
#define	SC_HALT		0x02
#define SC_NOVALUE	0x04
#define SC_NOTREADY	0x08
#define SC_SYNTAX	0x10

/* long jmp values */
#define	JMP_CONTINUE	2
#define JMP_ERROR	98
#define JMP_EXIT	99

/* rexx variables */
#define	RCVAR		0
#define	SIGLVAR		1

#ifdef ALIGN
#	define CTYPE	dword
#else
#	define CTYPE	word
#endif

/* ----------------- file structure --------------- */
typedef
struct trxfile {
	Lstr	filename;	/* filename		*/
	char	*filetype;	/* filetype in filename	*/
	Lstr	file;		/* actual file		*/
	struct trxfile *next;	/* prev in list		*/
} RxFile;

/* ------------- clause structure ----------------- */
typedef
struct tclause {
	size_t	code;		/* code start position	*/
	size_t	line;		/* line number in file	*/
	int	nesting;	/* nesting level	*/
	char 	*ptr;		/* pointer in file	*/
	RxFile	*fptr;		/* RxFile pointer	*/
} Clause;

/* ----------------- ident info ------------------- */
typedef
struct tidentinfo {
	int	id;		/* the last prg that set leaf value	*/
	int	stem;		/* if it is a stem			*/
	PBinLeaf leaf[1];	/* Variable array of leafs		*/
				/* Variable value if stem=0 OR		*/
				/* pointers to litterals		*/
} IdentInfo;

/* ------------ argument structure ---------------- */
typedef
struct targs {
	int	n;		/* number of args	*/
	PLstr	r;		/* return data		*/
	PLstr	a[MAXARGS];	/* argument pointers	*/
} Args;

/* ------------ internal rexxfunctions ------------ */
typedef
struct tbltfunc {
	char	*name;
	void	(*func)(int);
	int	opt;
} TBltFunc;

/* ----------- proc data structure ---------------- */
typedef
struct trxproc {
	int	id;		/* procedure id		*/
	int	calltype;	/* call type...		*/
	size_t	ip;		/* instruction pointer	*/
	size_t	stack;		/* stack position	*/
	size_t	stacktop;	/* stack after args	*/
	Scope	scope;		/* Variables		*/
	Args	arg;		/* stck pos of args	*/
	PLstr	env;		/* environment		*/
	int	digits;		/* numeric digits	*/
	int	fuzz;		/* numeric fuzz		*/
	int	form;		/* numeric form		*/
	int	condition;	/* signal on condition	*/
	PLstr	lbl_error;	/*	labels		*/
	PLstr	lbl_halt;	/*			*/
	PLstr	lbl_novalue;	/*			*/
	PLstr	lbl_notready;	/*			*/
	PLstr	lbl_syntax;	/*			*/
	int	codelen;	/* used in interpret_mn	*/
	int	clauselen;	/* used in interpret_mn	*/
	int	trace;		/* trace type		*/
	bool	interactive_trace;
} RxProc;

/* ------------- global variables ----------------- */
#ifdef __DEBUG__
EXTERN int	__debug__;
#endif
#if defined(WIN32) || defined(WCE)
EXTERN TCHAR	*_szRxAppKey;
#endif
EXTERN char	*_prgname;	/* point to argv[0]		*/
EXTERN jmp_buf	_error_trap;	/* error trap for compile	*/
EXTERN jmp_buf	_exit_trap;	/* exit from prg		*/

EXTERN DQueue	StackList;	/* dble queue of dble queues	*/

EXTERN RxFile	*rxfile;	/* rexx file list		*/
EXTERN int	RxReturnCode;	/* Global return code		*/

EXTERN int	_procidcnt;	/* procedure id counter		*/
EXTERN RxProc	*_Proc;		/* procedure & function array	*/
EXTERN int	_nesting;	/* cur nesting set by TraceCurline */
EXTERN int	_rx_proc;	/* current procedure id		*/
EXTERN int	_Proc_size;	/* number of items in proc list	*/

EXTERN PLstr	_code;		/* code of program		*/
EXTERN BinTree	_labels;	/* Labels			*/

EXTERN Args	Rxarg;		/* global arguments for internal routines */

EXTERN BinTree	Litterals;	/* Litterals			*/
EXTERN BinLeaf	*NullStr,	/* basic leaf Lstrings		*/
		*ZeroStr,
		*OneStr,
		*ResultStr,
		*SiglStr,
		*RCStr,
		*ErrorStr,
		*HaltStr,
		*SyntaxStr,
		*SystemStr,
		*NoValueStr,
		*NotReadyStr;

/* ============= function prototypes ============== */
void	RxInitialize( char *program_name );
void	RxFinalize( void );
int	RxRun( char *filename, PLstr programstr,
		PLstr arguments, PLstr tracestr, char *environment );

int	RxRegFunction( char *name, void (*func)(int), int opt );

void	RxHaltTrap( int );
void	RxSignalCondition( int );

int	RxRedirectCmd(PLstr cmd, int in, int out, PLstr resultstr);
int	RxExecuteCmd( PLstr cmd, PLstr env );

#undef EXTERN
#endif
