/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 12:52:25  bnv
 * Changed: To use the new macros
 *
 * Revision 1.1  1998/07/02 17:20:58  bnv
 * Initial Version
 *
 */

#include <ctype.h>
#include <lstring.h>

/* ----------------- Lwordpos ----------------- */
long
Lwordpos( const PLstr phrase, const PLstr s, long n )
{
	long	idx;
	long	lp,p;
	long	lk,k;

	L2STR(phrase);
	if (n>0) {
		idx = Lwordindex(s,n)-1;
		if (idx < 0) return LNOTFOUND;
	} else {
		n = 1;
		idx = 0;
		LSKIPBLANKS(*s,idx);
		L2STR(s);
	}
	lp = idx;

	lk=0; LSKIPBLANKS(*phrase,lk);
	if(lk>=LLEN(*phrase)) return LNOTFOUND;
	k = lk;  p = lp;

	while (1) {
		if (p >= LLEN(*s)) {
			LSKIPBLANKS(*phrase,k);
			if (k>=LLEN(*phrase))
				return n;
			else
				return 0;
		}
		if (k >= LLEN(*phrase)) {
			if (p>=LLEN(*s)) return n;
			if (ISSPACE(LSTR(*s)[p])) return n;
			k = lk;
			LSKIPWORD(*s,lp);
			LSKIPBLANKS(*s,lp);
			if (lp>=LLEN(*s)) return 0;
			p = lp;  n++;
		} else
			if (ISSPACE(LSTR(*phrase)[k])) {
				if (ISSPACE(LSTR(*s)[p])) {
					LSKIPBLANKS(*phrase,k);
					if (k>=LLEN(*phrase)) return n;
					LSKIPBLANKS(*s,p);
					if (p>=LLEN(*s)) return 0;
				} else {
					k = lk;
					LSKIPWORD(*s,lp);
					LSKIPBLANKS(*s,lp);
					if (lp>=LLEN(*s)) return 0;
					p = lp;  n++;
				}
			} else {
				if (LSTR(*phrase)[k] == LSTR(*s)[p]) {
					k++; p++;
				}  else {
					k = lk;
					LSKIPWORD(*s,lp);
					LSKIPBLANKS(*s,lp);
					if (lp >= LLEN(*s)) return 0;
					p = lp;  n++;
				}
			}
	}
} /* Lwordpos */
