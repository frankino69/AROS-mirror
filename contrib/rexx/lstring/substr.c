/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <string.h>
#include <lstring.h>

/* --------------------------- Lsubstr -------------------------------- */
/*    to       - Output Lstr                                            *
 *   from      - Input Lstr                                             *
 *   start     - an integer, can take values from [1,from length]       *
 *               if start<1 then start = 1                              *
 *   length    - negative value means rest of string (default)          *
 *               [1 - nnn] cuts string and pad's it if necessary.       *
 *    pad      - pad character                                          *
 * -------------------------------------------------------------------- */
void
Lsubstr(const PLstr to, const PLstr from,
	long start, long length, const char pad )
{
	size_t	l;

	L2STR(from);

	start--;
	if (start<0) start = 0;

	if (length<=0) {
		if (length==0 || start>=LLEN(*from)) {
			LZEROSTR(*to);
			return;
		}
		length = LLEN(*from) - start;
	}

	Lfx(to,(size_t)length);

	if (start<LLEN(*from)) {
		if (length+start>LLEN(*from)) {
			l = LLEN(*from) - (size_t)start;
			MEMMOVE( LSTR(*to), LSTR(*from)+start, l);
			MEMSET( LSTR(*to)+l, pad, (size_t)length-l);
		} else
			MEMMOVE( LSTR(*to), LSTR(*from)+start, (size_t)length);
	} else
		MEMSET(LSTR(*to),pad,(size_t)length);

	LTYPE(*to) = LSTRING_TY;
	LLEN(*to) = (size_t)length;
} /* Lstrsub */
