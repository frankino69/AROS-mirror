/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.3  1999/11/26 12:52:25  bnv
 * Changed: To use the new macros.
 *
 * Revision 1.2  1999/03/15 15:25:53  bnv
 * Corrected: initial value to prev
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ---------------- Llineout ------------------- */
int
Llineout( FILEP f, const PLstr line, long *curline, long start )
{
	int	ch,prev='\n';

	/* find current line */
	if (start>=0) {
		if (*curline>start) {
			*curline = 1;
			FSEEK(f,0,SEEK_SET);
		}
		while (start>*curline) {
			ch = FGETC(f);
			if (ch==-1) {
				if (prev!='\n') (*curline)++;
				break;
			}
			if (ch=='\n') (*curline)++;
			prev = ch;
		}
		while (start > *curline) {
			FPUTC('\n',f);
			(*curline)++;
		}
	}

	Lwrite(f,line,TRUE);
	(*curline)++;
	return 0;		/* if everything ok */
} /* Llineout */
