/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:16:35  bnv
 * Initial revision
 *
 */

#include <math.h>
#include <lstring.h>

/* ------------------ Labs ---------------------- */
void
Labs( const PLstr to, const PLstr num )
{
	L2NUM(num);

	switch (LTYPE(*num)) {
		case LINTEGER_TY:
			Licpy(to,labs(LINT(*num)));
			break;
		case LREAL_TY:
			Lrcpy(to,fabs(LREAL(*num)));
			break;
	}
} /* Labs */
