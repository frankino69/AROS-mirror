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

#include <lstring.h>

/* ------------------ Lx2d ------------------- */
void
Lx2d( const PLstr to, const PLstr from, long n )
{
	Lstr	tmp;
	int	sign;

	LINITSTR(tmp);

	if (n<=0) {
		Lx2c(&tmp,from);
		Lc2d(to,&tmp,0);
	} else {
		if (n>8) n=8;
		Lspace(&tmp,from,0,' ');
		Lright(to,&tmp,n,'0');
		sign = HEXVAL(LSTR(*to)[0]) & 0x8;
		Lx2c(&tmp,to);
		Lc2d(to,&tmp,0);
		if (sign) {
			if (n==sizeof(long)*2)
				LINT(*to) = -(~LINT(*to) + 1);
			else
				LINT(*to) = LINT(*to) - (1L << (n*4));
		}


		/****
		if ((LLEN(*to)&1) && LSTR(*to)[0]>'7') {
			Lright(&tmp,to,LLEN(*to)+1,'f');
			Lstrcpy(to,&tmp);
		}
		Lx2c(&tmp,to);
		Lc2d(to,&tmp,n/2);
		****/
	}
	LFREESTR(tmp);
} /* Lx2d */
