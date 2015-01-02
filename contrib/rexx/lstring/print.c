/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.5  1999/11/26 12:52:25  bnv
 * Added: Windows CE support
 * Changed: the ANSI_PRINTF to keep the gcc compiler happy
 *
 * Revision 1.4  1999/05/26 16:47:42  bnv
 * Gene corrections in RXCONIO
 *
 * Revision 1.3  1999/03/10 16:55:55  bnv
 * Correction for RXCONIO
 *
 * Revision 1.2  1999/02/10 15:45:16  bnv
 * RXCONIO support by Generoso Martello
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

#ifdef RXCONIO
#	define ANSI_FPRINTF(fd,fs,ff)	if (fd==STDOUT) \
				cprintf(fs,ff); else fprintf(fd,fs,ff)
#	define ANSI_FPUTS(fd,fs)	if (fd==STDOUT) \
				cprintf(fs); else fprintf(fd,fs)
#else
#	define ANSI_FPRINTF(fd,fs,ff)	fprintf(fd,fs,ff)
#	define ANSI_FPUTS(fd,fs)	fprintf(fd,fs)
#endif

/* ---------------- Lprint ------------------- */
void
Lprint( FILEP f, const PLstr str )
{
	size_t	l;
	char	*c;
#ifdef WIN
	char	s[20];
#endif

#ifndef WIN
	if (str==NULL) {
		ANSI_FPUTS(f,"<NULL>");
		return;
	}
#endif

	switch (LTYPE(*str)) {
		case LSTRING_TY:
			c = LSTR(*str);
			for (l=0; l<LLEN(*str); l++)
#ifdef RXCONIO
				if (f==STDOUT) {
					putch(*c++);
				} else
#endif
				FPUTC(*c++,f);
			break;

		case LINTEGER_TY:
#ifdef WIN
			FPUTS(LTOA(LINT(*str),s,10), f);
#else
			ANSI_FPRINTF(f,"%ld", LINT(*str));
#endif
			break;

		case LREAL_TY:
#ifdef WIN
			FPUTS(GCVT(LREAL(*str),lNumericDigits,s), f);
#else
			ANSI_FPRINTF(f, lFormatStringToReal, LREAL(*str));
#endif
			break;
	}
} /* Lprint */
