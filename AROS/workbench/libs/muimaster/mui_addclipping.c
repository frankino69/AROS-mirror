/*
    Copyright � 2002, The AROS Development Team. 
    All rights reserved.
    
    $Id$
*/

#include <proto/graphics.h>
#include <proto/layers.h>
#ifdef __AROS__
#include <proto/muimaster.h>
#endif

#include "support.h"

#include "mui.h"
#include "muimaster_intern.h"

/*****************************************************************************

    NAME */
	AROS_LH5(APTR, MUI_AddClipping,

/*  SYNOPSIS */
	AROS_LHA(struct MUI_RenderInfo *, mri, A0),
	AROS_LHA(WORD, left, D0),
	AROS_LHA(WORD, top, D1),
	AROS_LHA(WORD, width, D2),
	AROS_LHA(WORD, height, D3),

/*  LOCATION */
	struct Library *, MUIMasterBase, 24, MUIMaster)

/*  FUNCTION

    INPUTS

    RESULT

    NOTES

    EXAMPLE

    BUGS
	The function itself is a bug ;-) Remove it!

    SEE ALSO

    INTERNALS

    HISTORY

*****************************************************************************/
{
    AROS_LIBFUNC_INIT
    AROS_LIBBASE_EXT_DECL(struct MUIMasterBase *,MUIMasterBase)

    struct Region   	*r;
    struct Rectangle 	 rect;
    APTR    	    	 handle;
    
    if ((width >= MUI_MAXMAX) || (height >= MUI_MAXMAX))
        return (APTR)-1;

    if (mri->mri_rCount > 0)
    {
	if (isRegionWithinBounds(mri->mri_rArray[mri->mri_rCount-1], left, top, width, height))
	    return (APTR)-1;
    }

    if ((r = NewRegion()) == NULL)
        return (APTR)-1;

    rect.MinX = left;
    rect.MinY = top;
    rect.MaxX = left + width  - 1;
    rect.MaxY = top  + height - 1;
    OrRectRegion(r, &rect);

    handle = MUI_AddClipRegion(mri, r);

    if (handle == (APTR)-1)
    {
    	DisposeRegion(r);
    }
    
    return handle;
    
    AROS_LIBFUNC_EXIT

} /* MUIA_AddClipping */
