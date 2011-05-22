/*
    Copyright � 1995-2011, The AROS Development Team. All rights reserved.
    $Id$
*/

#include "__arosc_privdata.h"

#include <aros/symbolsets.h>
#include <sys/types.h>
#include <sys/stat.h>

#include LC_LIBDEFS_FILE

/*****************************************************************************

    NAME */

	mode_t umask(

/*  SYNOPSIS */
	mode_t numask)

/*  FUNCTION

    INPUTS

    RESULT

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

******************************************************************************/
{
    struct aroscbase *aroscbase = __get_aroscbase();
    mode_t oumask = aroscbase->acb_umask;

    aroscbase->acb_umask = numask;

    return oumask;
}

static int __umask_init(void)
{
    struct aroscbase *aroscbase = __get_aroscbase(),
                     *paroscbase;
    
    paroscbase = GM_GETPARENTBASEID2(aroscbase);

    /* FIXME: Implement umask() properly */

    if (paroscbase && (paroscbase->acb_flags & (VFORK_PARENT | EXEC_PARENT)))
        aroscbase->acb_umask = paroscbase->acb_umask;
    else
        aroscbase->acb_umask = S_IWGRP|S_IWOTH;

    return 1;
}

ADD2OPENLIB(__umask_init, 0);
