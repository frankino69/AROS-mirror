/*
    (C) 1995-96 AROS - The Amiga Replacement OS
    $Id$

    Desc:
    Lang: english
*/
#include <proto/aros.h>
#include "icon_intern.h"

extern const IPTR IconDesc[];

/*****************************************************************************

    NAME */
#include <clib/icon_protos.h>

	AROS_LH1(void, FreeDiskObject,

/*  SYNOPSIS */
	AROS_LHA(struct DiskObject *, diskobj, A0),

/*  LOCATION */
	struct Library *, IconBase, 15, Icon)

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
    AROS_LIBBASE_EXT_DECL(struct Library *,IconBase)

    FreeStruct ((APTR)diskobj, IconDesc);

    AROS_LIBFUNC_EXIT
} /* FreeDiskObject */
