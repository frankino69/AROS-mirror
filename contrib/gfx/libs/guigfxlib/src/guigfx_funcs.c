#include <guigfx/guigfx.h>
#include <aros/libcall.h>

#include "guigfx_global.h"
#include "guigfx_libprotos.h"

AROS_LH4(APTR, MakePictureA,
    AROS_LHA(APTR, data, A0),
    AROS_LHA(UWORD, totalsourcewidth, D0),
    AROS_LHA(UWORD, totalsourceheight, D1),
    AROS_LHA(struct TagItem *, taglist, A1),
    struct Library *, GuiGFXBase, 5, GuiGFX)
{
    AROS_LIBFUNC_INIT

    return MakePictureA(data, totalsourcewidth, totalsourceheight, taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH2(APTR, LoadPictureA,
    AROS_LHA(STRPTR, filename, A0),
    AROS_LHA(struct TagItem *, taglist, A1),
    struct Library *, GuiGFXBase, 6, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return LoadPictureA(filename, taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH7(APTR, ReadPictureA,
    AROS_LHA(struct RastPort *, rp, A0),
    AROS_LHA(struct ColorMap *, cm, A1),
    AROS_LHA(UWORD, x, D0),
    AROS_LHA(UWORD, y, D1),
    AROS_LHA(UWORD, width, D2),
    AROS_LHA(UWORD, height, D3),
    AROS_LHA(struct TagItem *, taglist, A2),
    struct Library *, GuiGFXBase, 7, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return ReadPictureA(rp, cm, x, y, width, height, taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH2(APTR, ClonePictureA,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(struct TagItem *, taglist, A1),
    struct Library *, GuiGFXBase, 8, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return ClonePictureA(pic, taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, DeletePicture,
    AROS_LHA(APTR, pic, A0),
    struct Library *, GuiGFXBase, 9, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    DeletePicture(pic);
    
    AROS_LIBFUNC_EXIT
}


AROS_LH1(BOOL, UpdatePicture,
    AROS_LHA(APTR, pic, A0),
    struct Library *, GuiGFXBase, 10, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return UpdatePicture(pic);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH3(APTR, AddPictureA,
    AROS_LHA(APTR, psm, A0),
    AROS_LHA(APTR, pic, A1),
    AROS_LHA(struct TagItem *, taglist, A2),
    struct Library *, GuiGFXBase, 11, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return AddPictureA(psm, pic, taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH3(APTR, AddPaletteA,
    AROS_LHA(APTR, psm, A0),
    AROS_LHA(APTR, palette, A1),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 12, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return AddPaletteA(psm, palette, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH5(APTR, AddPixelArrayA,
    AROS_LHA(APTR, psm, A0),
    AROS_LHA(APTR, array, A1),
    AROS_LHA(UWORD, width, D0),
    AROS_LHA(UWORD, height, D1),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 13, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return AddPixelArrayA(psm, array, width, height, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, RemColorHandle,
    AROS_LHA(APTR, ch, A0),
    struct Library *, GuiGFXBase, 14, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    RemColorHandle(ch);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(APTR, CreatePenShareMapA,
    AROS_LHA(struct TagItem *, taglist, A0),
    struct Library *, GuiGFXBase, 15, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return CreatePenShareMapA(taglist);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, DeletePenShareMap,
    AROS_LHA(APTR, psm, A0),
    struct Library *, GuiGFXBase, 16, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    DeletePenShareMap(psm);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH4(APTR, ObtainDrawHandleA,
    AROS_LHA(APTR, psm, A0),
    AROS_LHA(struct RastPort *, rp, A1),
    AROS_LHA(struct ColorMap *, cm, A2),
    AROS_LHA(struct TagItem *, tags, A3),
    struct Library *, GuiGFXBase, 17, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return ObtainDrawHandleA(psm, rp, cm, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, ReleaseDrawHandle,
    AROS_LHA(APTR, dh, A0),
    struct Library *, GuiGFXBase, 18, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    ReleaseDrawHandle(dh);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH5(BOOL, DrawPictureA,
    AROS_LHA(APTR, dh, A0),
    AROS_LHA(APTR, pic, A1),
    AROS_LHA(UWORD, x, D0),
    AROS_LHA(UWORD, y, D1),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 19, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return DrawPictureA(dh, pic, x, y, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH4(BOOL, MapPaletteA,
    AROS_LHA(APTR, dh, A0),
    AROS_LHA(APTR, palette, A1),
    AROS_LHA(UBYTE *, pentab, A2),
    AROS_LHA(struct TagItem *, tags, A3),
    struct Library *, GuiGFXBase, 20, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return MapPaletteA(dh, palette, pentab, tags);
       
    AROS_LIBFUNC_EXIT
}

AROS_LH3(LONG, MapPenA,
    AROS_LHA(APTR, dh, A0),
    AROS_LHA(ULONG, rgb, D0),
    AROS_LHA(struct TagItem *, tags, A1),
    struct Library *, GuiGFXBase, 21, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return MapPenA(dh, rgb, tags);
        
    AROS_LIBFUNC_EXIT
}

AROS_LH3(struct BitMap *, CreatePictureBitMapA,
    AROS_LHA(APTR, dh, A0),
    AROS_LHA(APTR, pic, A1),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 22, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return CreatePictureBitMapA(dh, pic, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH3(ULONG, DoPictureMethodA,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(ULONG, method, D0),
    AROS_LHA(IPTR *, arg, A1),
    struct Library *, GuiGFXBase, 23, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return DoPictureMethodA(pic, method, arg);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH2(ULONG, GetPictureAttrsA,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(struct TagItem *, tags, A1),
    struct Library *, GuiGFXBase, 24, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return GetPictureAttrsA(pic, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH3(ULONG, LockPictureA,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(ULONG, lockmode, D0),
    AROS_LHA(ULONG *, arg, A1),
    struct Library *, GuiGFXBase, 25, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return LockPictureA(pic, lockmode, arg);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH2(void, UnLockPicture,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(ULONG, lockmode, D0),
    struct Library *, GuiGFXBase, 26, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    UnLockPicture(pic, lockmode);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH2(BOOL, IsPictureA,
    AROS_LHA(char *, filename, A0),
    AROS_LHA(struct TagItem *, tags, A1),
    struct Library *, GuiGFXBase, 27, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return IsPictureA(filename, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH6(APTR, CreateDirectDrawHandleA,
    AROS_LHA(APTR, dh, A0),
    AROS_LHA(UWORD, sourcewidth, D0),
    AROS_LHA(UWORD, sourceheight, D1),
    AROS_LHA(UWORD, destwidth, D2),
    AROS_LHA(UWORD, destheight, D3),
    AROS_LHA(struct TagItem *, tags, A1),
    struct Library *, GuiGFXBase, 28, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return CreateDirectDrawHandleA(dh, sourcewidth, sourceheight, destwidth, destheight, tags);
    
    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, DeleteDirectDrawHandle,
    AROS_LHA(APTR, ddh, A0),
    struct Library *, GuiGFXBase, 29, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    DeleteDirectDrawHandle(ddh);
    
    AROS_LIBFUNC_EXIT
}


AROS_LH5(BOOL, DirectDrawTrueColorA,
    AROS_LHA(APTR, ddh, A0),
    AROS_LHA(ULONG *, array, A1),
    AROS_LHA(UWORD, x, D0),
    AROS_LHA(ULONG, y, D1),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 30, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return DirectDrawTrueColorA(ddh, array, x, y, tags);
        
    AROS_LIBFUNC_EXIT
}

AROS_LH4(BOOL, CreatePictureMaskA,
    AROS_LHA(APTR, pic, A0),
    AROS_LHA(UBYTE *, array, A1),
    AROS_LHA(UWORD, arraywidth, D0),
    AROS_LHA(struct TagItem *, tags, A2),
    struct Library *, GuiGFXBase, 31, GuiGFX)
{
    AROS_LIBFUNC_INIT
    
    return CreatePictureMaskA(pic, array, arraywidth, tags);
    
    AROS_LIBFUNC_EXIT
}

