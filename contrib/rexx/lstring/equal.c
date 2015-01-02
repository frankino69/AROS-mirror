/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.3  1999/11/26 09:56:55  bnv
 * Changed: To use the new macros.
 * Changed: From char* to byte* comparison, to avoid signed char problems.
 * Changed: To use the lLastScannedNumber
 *
 * Revision 1.2  1998/11/10 13:36:14  bnv
 * Comparison for reals is done with fabs(a-b)<smallnumber
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <math.h>
#include <ctype.h>
#include <string.h>
#include <lstring.h>

/* -------------------- Lequal ----------------- */
int
Lequal(const PLstr A, const PLstr B)
{
	int	ta, tb;
	byte	*a, *b;		/* start position in string */
	byte	*ae, *be;	/* ending position in string */
	double	ra, rb;

	if (LTYPE(*A)==LSTRING_TY) {
		ta = _Lisnum(A);

		/* check to see if the first argument is string? */
		if (ta == LSTRING_TY) {
			L2STR(B);	/* make string and the second	*/
			goto eq_str;	/* go and check strings		*/
		}

		ra = lLastScannedNumber;
	} else {
		ta = LTYPE(*A);
		ra = TOREAL(*A);
	}

	if (LTYPE(*B)==LSTRING_TY) {
		tb = _Lisnum(B);
		rb = lLastScannedNumber;
	} else {
		tb = LTYPE(*B);
		rb = TOREAL(*B);
	}

	/* is B also a number */
	if (tb != LSTRING_TY) {
		if (fabs(ra-rb)<=1E-14)
			return 0;
		else
		if (ra>rb)
			return 1;
		else
			return -1;
	}

	/* nope it was a string */
	L2STR(A);		/* convert A string */
eq_str:
	a = (byte*)LSTR(*A);
	ae = a + LLEN(*A);
	for(; (a<ae) && ISSPACE(*a); a++) ;

	b = (byte*)LSTR(*B);
	be = b + LLEN(*B);
	for(; (b<be) && ISSPACE(*b); b++) ;

	for(;(a<ae) && (b<be) && (*a==*b); a++,b++) ;

	for(; (a<ae) && ISSPACE(*a);a++) ;
	for(; (b<be) && ISSPACE(*b);b++) ;

	if (a==ae && b==be)
		return 0;
	else
	if (a<ae && b<be)
		return (*a<*b) ? -1 : 1 ;
	else 
		return (a<ae) ? 1 : -1 ;
} /* Lequal */
