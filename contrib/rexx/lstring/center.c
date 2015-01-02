/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:17:00  bnv
 * Initial revision
 *
 */

#include <string.h>
#include <lstring.h>

/* ------------------ Lcenter ----------------- */
void
Lcenter( const PLstr to, const PLstr from, const long length, const char pad)
{
	long	i,a;

	if (length<=0) {
		LZEROSTR(*to);
		return;
	}

	L2STR(to);
	L2STR(from);
	i = length - LLEN(*from);

	if (!i) Lstrcpy(to,from);
	else
		if (i < 0) {
			i = -i;    a = i / 2;
			_Lsubstr(to, from, (size_t)a+1, (size_t)length);
		} else  {
			a = i / 2;
			Lstrset(to,length,pad);
			MEMCPY( LSTR(*to)+a, LSTR(*from), LLEN(*from) );
		}
} /* Lcenter */
