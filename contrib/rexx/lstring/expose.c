/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 09:56:55  bnv
 * Changed: Formatting
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* -----------------  expose ---------------- */
void
Lexpose( const PLstr to, const PLstr A, const PLstr B )
{
	double ar,r;
	long   bi;
	bool   minusA;
	bool   minusB;

	ar = Lrdreal(A);
	bi = Lrdint(B);

	if (ar < 0 ) {
		if (ODD(bi))
			minusA = TRUE;
		else
			minusA = FALSE;
		ar = - ar;
	} else
		minusA = FALSE;

	if (bi < 0 ) {
		minusB = TRUE;
		bi = - bi;
	} else
		minusB = FALSE;
	r = 1;

	while (bi != 0) {
		if (ODD(bi)) r *= ar;
		ar *= ar;
		bi /= 2;
	}
	if (minusA) r = -r;

	if (minusB)
		LREAL(*to) = 1/r;
	else
		LREAL(*to) = r;

	LTYPE(*to) = LREAL_TY;
	LLEN(*to)  = sizeof(double);
} /* Lexpose */
