/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:39  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 13:13:47  bnv
 * Changed: The formatting of the code.
 *
 * Revision 1.1  1998/07/02 17:34:50  bnv
 * Initial revision
 *
 */

#include <string.h>

#include <lerror.h>
#include <lstring.h>

#include <rexx.h>
#include <rxdefs.h>

/* --------------------------------------------------------------- */
/* SPACE(string(,(n)(,pad)))                                       */
/* --------------------------------------------------------------- */
void
R_space( )
{
	long	n;
	char	pad;

	if (!IN_RANGE(1,ARGN,3)) Lerror(ERR_INCORRECT_CALL,0);
	must_exist(1);
	if (exist(2)) {
		n = Lrdint(ARG2);
		if (n<0) Lerror(ERR_INCORRECT_CALL,0);
	} else
		n = 1;
	get_pad(3,pad);

	Lspace(ARGR, ARG1, n, pad);
} /* R_space */

/* --------------------------------------------------------------- */
/*  WORD(string,n)                                                 */
/* --------------------------------------------------------------- */
/*  WORDINDEX(string,n)                                            */
/* --------------------------------------------------------------- */
/*  WORDLENGTH(string,i)                                           */
/* --------------------------------------------------------------- */
void
R_SI( const int func )
{
	long     n;

	if (ARGN!=2) Lerror(ERR_INCORRECT_CALL,0);
	must_exist(1);
	get_i(2,n);

	switch (func) {
		case f_word:
			Lword(ARGR,ARG1,n);
			break;

		case f_wordlength:
			Licpy(ARGR,Lwordlength(ARG1,n));
			break;

		case f_wordindex:
			Licpy(ARGR,Lwordindex(ARG1,n));
			break;

		default:
			Lerror(ERR_INTERPRETER_FAILURE,0);
	} /* switch */
} /* R_SI */
