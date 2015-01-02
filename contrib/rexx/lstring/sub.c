/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 12:52:25  bnv
 * Changed: To use lLastScannedNumber.
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lerror.h>
#include <lstring.h>

/* ---------------- Lsub ------------------- */
void
Lsub( const PLstr to, const PLstr A, const PLstr B)
{
	int	ta, tb;
	double	r;

	if (LTYPE(*A) == LSTRING_TY) {
		ta = _Lisnum(A);
		if (ta==LSTRING_TY) Lerror(ERR_BAD_ARITHMETIC,0);
		/*//r = strtod(LSTR(*A),NULL); */
		r = lLastScannedNumber;
	} else {
		ta = LTYPE(*A);
		r = TOREAL(*A);
	}

	if (LTYPE(*B) == LSTRING_TY) {
		tb = _Lisnum(B);
		if (tb==LSTRING_TY) Lerror(ERR_BAD_ARITHMETIC,0);
		/*//r -= strtod(LSTR(*B),NULL); */
		r -= lLastScannedNumber;
	} else {
		tb = LTYPE(*B);
		r -= TOREAL(*B);
	}

	if ( (ta == LINTEGER_TY) && (tb == LINTEGER_TY) ) {
		LINT(*to)  = (long)r;
		LTYPE(*to) = LINTEGER_TY;
		LLEN(*to)  = sizeof(long);
	} else {
		LREAL(*to) = r;
		LTYPE(*to) = LREAL_TY;
		LLEN(*to)  = sizeof(double);
	}
} /* Lsub */
