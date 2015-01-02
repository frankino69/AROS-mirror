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

#include <lstring.h>

/* -------------------- Ld2c -------------------- */
void
Ld2c( const PLstr to, const PLstr from, long n )
{
	int   i;
	long  num,n2;
	bool  negative;

	num = Lrdint(from);

	if (n==0) {
		LZEROSTR(*to);
		return;
	}
	if (n<0) n=0;

	negative = (num<0);
	if (negative)
		num = -num-1;

	if (n>sizeof(long)) n=sizeof(long);
	Lfx(to,(size_t)n);

	n2 = n? n: sizeof(long);
	for (i=0; num && i<n2; i++) {
		LSTR(*to)[i] = num & 0xFF;
		if (negative)
			LSTR(*to)[i] ^= 0xFF;
		num >>= 8;
	}
	if (i==0) {
		LSTR(*to)[i] = 0x00;
		if (negative)
			LSTR(*to)[i] ^= 0xFF;
		i++;
	}

	while (i<n) {
		LSTR(*to)[i] = negative? 0xFF : 0x00;
		i++;
	}

	LTYPE(*to) = LSTRING_TY;
	LLEN(*to) = i;
	Lreverse(to);
} /* Ld2c */
