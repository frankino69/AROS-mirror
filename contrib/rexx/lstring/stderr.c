/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:38  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/26 12:52:25  bnv
 * Changed: To use new macros
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

#ifdef WCE
#	error "Lstderr: should not be included in the CE version"
#endif
/* ------------------ Lstderr ------------------- */
void
Lstderr( const int errno, const int subno, ... ) 
{
	Lstr	errmsg;
	va_list	ap;

	LINITSTR(errmsg);

	va_start(ap,subno);
	Lerrortext(&errmsg,errno,subno,&ap);
	va_end(ap);

	if (LLEN(errmsg)==0)
		fprintf(STDERR,"Ooops unknown error %d.%d!!!\n",errno,subno);
	else {
		LASCIIZ(errmsg);
		if (subno==0)
			fprintf(STDERR,"Error %d: %s\n",errno,LSTR(errmsg));
		else 
			fprintf(STDERR,"Error %d.%d: %s\n",errno,subno,LSTR(errmsg));
	}

	LFREESTR(errmsg);
	exit(errno);
} /* Lstderr */
