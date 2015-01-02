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

/* ---------------- Llinein ------------------- */
void
Llinein( FILEP f, const PLstr line, long *curline, long start, long length )
{
	int	ch,prev='\n';
	Lstr	aux;

	/* initialise line */
	LZEROSTR(*line);

	/* find current line */
	if (start>=0) {
		if (*curline>start) {
			*curline = 1;
			FSEEK(f,0,SEEK_SET);
		}
		while (start>*curline) {
			ch = FGETC(f);
			if (ch==EOF) {
				if (prev!='\n') (*curline)++;
				break;
			}
			if (ch=='\n') (*curline)++;
			prev = ch;
		}
		if (start > *curline) return;
	}

	if (length<=0) return;

	if (length==1) {
		Lread(f,line,LREADLINE);
		(*curline)++;
	} else {
		LINITSTR(aux);
		while (length) {
			Lread(f,&aux,LREADLINE);
			Lstrcat(line,&aux);
			if (length>1)
				Lcat(line,"\n");
			(*curline)++;
			length--;
		}
		LFREESTR(aux);
	}
} /* Llinein */
