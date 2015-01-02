/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 12:52:25  bnv
 * Changed: To use the new macros.
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ---------------- Llines ------------------- */
long
Llines( FILEP f )
{
	long	pos,l;
	int	ch,prev;

	pos = FTELL(f);		/* read current position */
	l = 0;
	prev = ' ';
	while (1) {
		ch = FGETC(f);
		if (ch==-1) {
			if (prev!='\n') l++;
			break;
		}
		if (ch=='\n') l++;
		prev = ch;
	}
	FSEEK(f,pos,SEEK_SET);
	return l;
} /* Llines */
