/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:20:58  bnv
 * Initial Version
 *
 */

#include <string.h>
#include <lstring.h>

/* --------------------- Lverify  ----------------------- *
 *  str      -  string that we check every char           *
 * 		if it exists on 'ref'                     *
 *  ref      -  reference characters                      *
 *  match    -  FALSE = find non matching chars           *
 *		TRUE  = find only matching chars          *
 *  start    -	starting position [1,len]                 *
 * returns                                                *
 *    0		if every char is found (or not found)     *
 * 		according to match                        *
 *   pos	else non matching (or matching) position  *
 * ------------------------------------------------------ */
long
Lverify( const PLstr str, const PLstr ref, const bool match, long start )
{
	bool	found;

	L2STR(str);
	L2STR(ref);

	start--;
	if (start<0) start = 0;
	if (start >= LLEN(*str)) return LNOTFOUND;

	for (; start<LLEN(*str); start++) {
		found = (MEMCHR(LSTR(*ref), LSTR(*str)[start], LLEN(*ref))==NULL);
		if (found ^ match) return start+1;
	}
	return LNOTFOUND;
} /* Lverify */
