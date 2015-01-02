/**********************************************************************************
 * .
 *
 *
 **************************************************
 * This code was created by Peter Harvey @ CodeByDesign.
 * Released under LGPL 28.JAN.99
 *
 * Contributions from...
 * -----------------------------------------------
 * Peter Harvey		- pharvey@codebydesign.com
 **************************************************/

#include "inifile_intern.h"
#include "ini.h"
#include <aros/libcall.h>

/*****************************************************************************

    NAME */
	AROS_LH1(int, iniDelete,

/*  SYNOPSIS */
	AROS_LHA(HINI, hIni, D0),
	
/*  LOCATION */
	struct Library *, inifileBase, 13, inifile)

/*  FUNCTION

    INPUTS

    RESULT

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

    HISTORY

*****************************************************************************/
{
    AROS_LIBFUNC_INIT

    /* SANITY CHECKS */
    if ( hIni == NULL )
        return INI_ERROR;

	/* REMOVE ALL SUBORDINATE INFO */
	iniObjectFirst( hIni );
	while ( iniObjectDelete( hIni ) == INI_SUCCESS )
	{
	}

	return INI_SUCCESS;

    AROS_LIBFUNC_EXIT
} /* iniDelete */

