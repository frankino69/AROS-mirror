#ifndef _GTLAYOUT_GLOBAL_H
#include "gtlayout_global.h"
#endif

#include <aros/system.h>

/*****************************************************************************/

#include <stdarg.h>

/*****************************************************************************/

#include "Assert.h"

/*****************************************************************************/

LayoutHandle *
LT_CreateHandleTags(struct Screen *Screen, Tag tag1,...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, LayoutHandle *)
	retval = LT_CreateHandleTagList(Screen, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_SLOWSTACKTAGS_POST
}

VOID
LT_AddL(LayoutHandle *handle,LONG type,ULONG labelID,LONG id, Tag tag1, ...)
{
	AROS_NR_SLOWSTACKTAGS_PRE(tag1)

	if(handle)
	{
		if(handle->LocaleHook)
		{
			STRPTR label;

			label = (STRPTR)CallHookPkt(handle->LocaleHook, handle, (APTR)(IPTR)labelID);

			LT_AddA(handle, type, label, id, AROS_SLOWSTACKTAGS_ARG(tag1));
		}
		else
			handle->Failed = TRUE;
	}

	AROS_NR_SLOWSTACKTAGS_POST
}

VOID
LT_New(LayoutHandle *handle, Tag tag1,...)	/* link library only */
{
	AROS_NR_SLOWSTACKTAGS_PRE(tag1)
	LT_NewA(handle, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_NR_SLOWSTACKTAGS_POST
}

VOID
LT_Add(
	LayoutHandle *	Handle,
	LONG			Type,
	STRPTR			Label,
	LONG			ID,
	Tag                     tag1,
					...)	/* link library only */
{
	AROS_NR_SLOWSTACKTAGS_PRE(tag1)
	LT_AddA(Handle, Type, Label, ID, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_NR_SLOWSTACKTAGS_POST
}

struct Window *
LT_Layout(LayoutHandle *handle,
	STRPTR title,
	struct IBox *bounds,
	LONG extraWidth, LONG extraHeight,
	ULONG IDCMP,
	LONG align,
	Tag tag1, ...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, struct Window *)

	retval = LT_Build(handle,
		LAWN_Title,			title,
		LAWN_Bounds,		bounds,
		LAWN_ExtraWidth,	extraWidth,
		LAWN_ExtraHeight,	extraHeight,
		LAWN_IDCMP,			IDCMP,
		LAWN_AlignWindow,	align,
		TAG_MORE,AROS_SLOWSTACKTAGS_ARG(tag1));

	AROS_SLOWSTACKTAGS_POST

}

struct Menu *
LT_LayoutMenus(LayoutHandle *handle, struct NewMenu *menuTemplate, Tag tag1,...)
{
        AROS_SLOWSTACKTAGS_PRE_AS(tag1, struct Menu *)
        retval = LT_LayoutMenusA(handle, menuTemplate, AROS_SLOWSTACKTAGS_ARG(tag1));
        AROS_SLOWSTACKTAGS_POST
}

struct Window *
LT_Build(LayoutHandle *Handle, Tag tag1, ...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, struct Window *)
	retval = LT_BuildA(Handle, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_SLOWSTACKTAGS_POST
}

VOID
LT_SetAttributes(LayoutHandle *handle, LONG id, Tag tag1,...)
{
	AROS_NR_SLOWSTACKTAGS_PRE(tag1)
	LT_SetAttributesA(handle, id, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_NR_SLOWSTACKTAGS_POST
}

IPTR
LT_GetAttributes(LayoutHandle *Handle, LONG ID, Tag tag1,...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, IPTR)
	retval = LT_GetAttributesA(Handle, ID, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_SLOWSTACKTAGS_POST
}

BOOL
LT_RebuildTags(LayoutHandle *Handle, BOOL Clear, Tag tag1,...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, BOOL)
	retval = LT_RebuildTagList(Handle, Clear, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_SLOWSTACKTAGS_POST
}

VOID
LT_MenuControlTags(struct Window *Window, struct Menu *Menu, Tag tag1,...)
{
	AROS_NR_SLOWSTACKTAGS_PRE(tag1)
	LT_MenuControlTagList(Window, Menu, AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_NR_SLOWSTACKTAGS_POST
}

struct Menu *
LT_NewMenuTags(Tag tag1,...)
{
	AROS_SLOWSTACKTAGS_PRE_AS(tag1, struct Menu *)
	retval = LT_NewMenuTagList(AROS_SLOWSTACKTAGS_ARG(tag1));
	AROS_SLOWSTACKTAGS_POST
}
