/*
    Copyright 2011, The AROS Development Team. All rights reserved.
    $Id$
*/

#ifndef HOSTGL_TYPES_H
#define HOSTGL_TYPES_H

#include <GL/arosmesa.h>

#include "hostgl_renderer_config.h"

#include "x11_hostlib.h"
#include "glx_hostlib.h"

struct arosmesa_framebuffer
{
    ULONG       width;
    ULONG       height;
    BOOL        resized;
    GLXFBConfig *fbconfigs;
};

/* AROSMesa context */
struct arosmesa_context
{
#if defined(RENDERER_SEPARATE_X_WINDOW)
    Window      XWindow;
    GLXWindow   glXWindow;
#endif
#if defined(RENDERER_PBUFFER_WPA)
    GLXPbuffer  glXPbuffer;
    ULONG       *swapbuffer;
    ULONG       *swapbufferline;
#endif
#if defined(RENDERER_PIXMAP_BLIT)
    XVisualInfo     *visinfo;
    struct BitMap   *glXPixmapBM;
    GLXPixmap       glXPixmap;
#endif
    GLXContext  glXctx;

    struct arosmesa_framebuffer *framebuffer;

    struct Window               *window;                /* Intuition window */
    struct Screen               *Screen;
    ULONG                       BitsPerPixel;
    
    /* Rastport 'visible' to user (window rasport, screen rastport)*/
    struct RastPort             *visible_rp;
    /* Rastport dimentions */
    ULONG                       visible_rp_width;       /* the rastport drawing area full size*/
    ULONG                       visible_rp_height;      /* the rastport drawing area full size*/

    /* Buffer information */
    ULONG                      top, bottom;            /* offsets due to window border */
    ULONG                      left, right;            /* offsets due to window border */    
};

#define SWAPBUFFER_BPP  (4) /* Swap buffer always has 4 bytes per pixel, even on 16bpp screens */

#endif /* HOSTGL_TYPES_H */
