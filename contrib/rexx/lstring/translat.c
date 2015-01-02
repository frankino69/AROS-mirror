/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/03/01 11:07:22  bnv
 * Added '{..}' to avoid nesting if () {} else {} errors.
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ---------------- Ltranslate ------------------- */
void
Ltranslate( const PLstr to, const PLstr from,
	const PLstr tableout, const PLstr tablein, const char pad )
{
	char     table[256];
	int      i;

	Lstrcpy(to,from);	L2STR(to);

	for (i=0; i<256; i++)
		table[i] = i;

	if (tableout)	L2STR(tableout);
	if (tablein)	L2STR(tablein);

	if (tablein) {
		for (i=LLEN(*tablein)-1; i>=0; i--)
			if (tableout) {
				if (i>=LLEN(*tableout))
					table[(byte)LSTR(*tablein)[i]]=pad;
				else
					table[(byte)LSTR(*tablein)[i]]=LSTR(*tableout)[i];
			} else
				table[(byte)LSTR(*tablein)[i]] = pad;
	} else {
		for (i=0; i<256; i++)
			if (tableout) {
				if (i >= LLEN(*tableout))
					table[i] = pad;
				else
					table[i] = LSTR(*tableout)[i];
			}
	}

	for (i=0; i<LLEN(*to); i++)
		LSTR(*to)[i] = table[ (byte) LSTR(*to)[i] ];
} /* Ltranslate */
