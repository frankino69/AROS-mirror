/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ----------------- Lindex ---------------------- */
/* haystack   - Lstr where to search               *
 *  needle    - Lstr to search                     *
 *    p       - starting position [1,haystack len] *
 *              if p < 1 then p = 1                *
 * returns  0 (NOTFOUND) is needle is not found    *
 * else returns position [1,haystack len]          *
 * ----------------------------------------------- */
long
Lindex( const PLstr haystack, const PLstr needle, long p)
{
	long	n,lp;

	p--;		/* for C string offset = 0, Rexx=1 */
	if (p<0) p = 0;

	L2STR(haystack);
	L2STR(needle);

	if (!LLEN(*needle)) {
		if (!LLEN(*haystack)) return LNOTFOUND;
		return p+1;
	}
	if (LLEN(*needle) > LLEN(*haystack)) return LNOTFOUND;
	lp = p-1;
	do {
		n = 0; p = lp+1;
		if (p >= LLEN(*haystack)) return LNOTFOUND;
		while (LSTR(*haystack)[p] != LSTR(*needle)[0]) {
			p++;
			if (p >= LLEN(*haystack)) return LNOTFOUND;
		}
		lp = p;
		while ( (LSTR(*haystack)[p]==LSTR(*needle)[n]) && (n<LLEN(*needle))) {
			if ((++n) >= LLEN(*needle)) return lp+1;
			p++;
			if (p >= LLEN(*haystack)) return LNOTFOUND;
		}
	} while (n<LLEN(*needle));
	return lp+1;
} /* Lindex */
