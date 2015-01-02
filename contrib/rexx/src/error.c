/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:39  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 13:13:47  bnv
 * Changed: To use the new macros
 *
 * Revision 1.1  1998/07/02 17:34:50  bnv
 * Initial revision
 *
 */

#include <stdarg.h>
#include <lstring.h>

#include <rexx.h>
#include <trace.h>
#include <compile.h>
#include <interpre.h>
#include <variable.h>
#include <nextsymb.h>

/* --- Global variable --- */
Lstr	errmsg;			/* initialise string from beggining  */

/* ---------------- RxHaltTrap ----------------- */
void
RxHaltTrap( int cnd )
{
	if (_Proc[_rx_proc].condition & SC_HALT)
		RxSignalCondition(SC_HALT);
	else
		Lerror(ERR_PROG_INTERRUPT,0);
} /* RxHaltTrap */

/* ---------------- RxSignalCondition -------------- */
void
RxSignalCondition( int cnd )
{
	PBinLeaf	leaf;
	RxFunc	*func;
	PLstr	cndstr=NULL;

/*///////// first we need to terminate all the interpret strings */
	switch (cnd) {
		case SC_ERROR:
			cndstr = _Proc[_rx_proc].lbl_error;
			break;
		case SC_HALT:
			cndstr = _Proc[_rx_proc].lbl_halt;
			break;
		case SC_NOVALUE:
			cndstr = _Proc[_rx_proc].lbl_novalue;
			break;
		case SC_NOTREADY:
			cndstr = _Proc[_rx_proc].lbl_notready;
			break;
		case SC_SYNTAX:
			cndstr = _Proc[_rx_proc].lbl_syntax;
			break;
	}
	leaf = BinFind(&_labels,cndstr);
	if (leaf==NULL || ((RxFunc*)(leaf->value))->label==UNKNOWN_LABEL) {
		if (cnd==SC_SYNTAX) /* disable the error handling */
			_Proc[_rx_proc].condition &= ~SC_SYNTAX;
		Lerror(ERR_UNEXISTENT_LABEL,1,cndstr);
	}
	func = (RxFunc*)(leaf->value);
	RxSetSpecialVar(SIGLVAR,TraceCurline(NULL,FALSE));
	Rxcip = (CIPTYPE*)((byte huge *)Rxcodestart + (size_t)(func->label));
	longjmp(_error_trap,JMP_CONTINUE);
} /* RxSignalCondition */

/* ------------------ Rerror ------------------- */
void
Rerror( int errno, int subno, ... ) 
{
	int	line;
	RxFile	*rxf;
	va_list	ap;

	if (_Proc[_rx_proc].condition & SC_SYNTAX) {
		RxSetSpecialVar(RCVAR,errno);
		if (symbolptr==NULL)	/* we are in intepret	*/
			RxSignalCondition(SC_SYNTAX);
		else {			/* we are in compile	*/
			RxReturnCode = errno;
			longjmp(_error_trap,JMP_ERROR);
		}
	} else {
		line = TraceCurline(&rxf,TRUE);
		if (symbolptr==NULL)	/* we are in intepret */
			RxSetSpecialVar(SIGLVAR,line);

#ifndef WIN
		va_start(ap,subno);
		Lerrortext(&errmsg,errno,subno,&ap);
		va_end(ap);

		if (LLEN(errmsg)==0)
			fprintf(STDERR," +++ Ooops unknown error %d.%d +++\n",errno,subno);
		else {
			LASCIIZ(errmsg);
			if (subno==0)
				fprintf(STDERR,
					"Error %d running %s, line %d: %s\n",
						errno,
						LSTR(rxf->filename),
						line,
						LSTR(errmsg));
			else 
				fprintf(STDERR,
					"Error %d.%d running %s, line %d: %s\n",
						errno,
						subno,
						LSTR(rxf->filename),
						line,
						LSTR(errmsg));
		}
#else
		{
			PUTS("Error ");
			PUTINT(errno,0,10);
			PUTS(" running ");
			PUTS(LSTR(rxf->filename));
			PUTS(" line ");
			PUTINT(line,0,10);
			PUTS(": ");
			Lerrortext(&errmsg,errno,subno,NULL);
			Lprint(NULL,&errmsg);
			PUTCHAR('\n');
		}
#endif
		RxReturnCode = errno;
		longjmp(_exit_trap,JMP_EXIT);
	}
} /* Rerror */
