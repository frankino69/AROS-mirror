/*
    (C) 1995 AROS - The Amiga Research OS
    $Id$

    Desc: Private graphics function for setting mouse pointer shape
    Lang: english
*/
#include "graphics_intern.h"
#include <exec/memory.h>
#include <graphics/rastport.h>
#include <proto/exec.h>
#include <oop/oop.h>

/*****************************************************************************

    NAME */
#include <graphics/rastport.h>
#include <proto/graphics.h>

	AROS_LH5(VOID , SetPointerShape,

/*  SYNOPSIS */
	AROS_LHA(UWORD *, shape, A0),
	AROS_LHA(UWORD, width, D0),
	AROS_LHA(UWORD, height, D1),
	AROS_LHA(UWORD, xoffset, D2),
	AROS_LHA(UWORD, yoffset, D3),

/*  LOCATION */
	struct GfxBase *, GfxBase, 186, Graphics)

/*  FUNCTION
	Set the current mouse pointer's shape.

    INPUTS

    RESULT

    NOTES
	This function is private and AROS specific.

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

    HISTORY
	29-10-95    digulla automatically created from
			    graphics_lib.fd and clib/graphics_protos.h

*****************************************************************************/
{
    AROS_LIBFUNC_INIT
    AROS_LIBBASE_EXT_DECL(struct GfxBase *,GfxBase)
    
    driver_SetPointerShape(shape, width, height, xoffset, yoffset, GfxBase);

    AROS_LIBFUNC_EXIT
} /* SetPointerShape */
