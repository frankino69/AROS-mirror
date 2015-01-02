/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 12:52:25  bnv
 * Changed: To use the fcvt()
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ---------------- Ltrunc ----------------- */
void
Ltrunc( const PLstr to, const PLstr from, long n)
{
#ifdef WCE
	char	*snum, *s;
	int	decp, sign;
#endif
	if (n<0) n = 0;

	if (!n) {
		Lstrcpy(to,from);
		L2REAL(to);
		LINT(*to)  = (long)LREAL(*to);
		LTYPE(*to) = LINTEGER_TY;
		LLEN(*to)  = sizeof(long);
	} else {
		L2REAL(from);
		Lfx(to,n+15);
#ifndef WCE
		sprintf(LSTR(*to),"%.*f", (int)n, LREAL(*from));
#else
//////// WARNING NO ROUNDING ON THE NUMBER IS DONE!
#define NDIG	20
		s = LSTR(*to);
		snum = FCVT(LREAL(*from), NDIG, &decp, &sign);
		if (sign) *s++ = '-';
		if (decp<0)		// Move it in the front
			decp += NDIG;
		if (decp>=0) {
			while (decp--)
				*s++ = *snum++;
			*s++ = '.';
		} else {
			*s++ = '0';
			*s++ = '.';
			while (decp++ && n--)
				*s++ = '0';
		}
		while (n--)
			*s++ = *snum++;
		*s = 0;
#endif
		LTYPE(*to) = LSTRING_TY;
		LLEN(*to)  = STRLEN(LSTR(*to));
	}
} /* R_trunc */
