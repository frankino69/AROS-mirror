/*
    Copyright � 2013, The AROS Development Team. All rights reserved.
    $Id$

    Desc: VideoCore Gfx Onscreen Bitmap Class.
    Lang: English.
*/

#define DEBUG 1
#include <aros/debug.h>

#define __OOP_NOATTRBASES__

#include <proto/oop.h>
#include <proto/vcmbox.h>
#include <proto/utility.h>
#include <assert.h>
#include <exec/memory.h>
#include <exec/lists.h>
#include <aros/symbolsets.h>
#include <graphics/rastport.h>
#include <graphics/gfx.h>
#include <hidd/graphics.h>
#include <oop/oop.h>

#include "videocoregfx_bitmap.h"
#include "videocoregfx_class.h"

#include LC_LIBDEFS_FILE

#ifdef VCMBoxBase
#undef VCMBoxBase
#endif

#define VCMBoxBase      (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxBase

#define MNAME_ROOT(x) VideoCoreGfxOnBM__Root__ ## x
#define MNAME_BM(x) VideoCoreGfxOnBM__Hidd_BitMap__ ## x

#define OnBitmap 1
#include "videocoregfx_bitmap_common.c"

/*********** BitMap::New() *************************************/

OOP_Object *MNAME_ROOT(New)(OOP_Class *cl, OOP_Object *o, struct pRoot_New *msg)
{
    EnterFunc(bug("VideoCoreGfx.OnBitMap::New()\n"));
    o = (OOP_Object *)OOP_DoSuperMethod(cl, o, (OOP_Msg) msg);
    if (o)
    {
        struct BitmapData *data;
        OOP_Object *pf;
        IPTR width, height, depth;
        HIDDT_ModeID modeid;

        /* clear all data  */
        data = OOP_INST_DATA(cl, o);
        memset(data, 0, sizeof(struct BitmapData));

        /* Get attr values */
        OOP_GetAttr(o, aHidd_BitMap_ModeID, &modeid);
        OOP_GetAttr(o, aHidd_BitMap_Width, &width);
        OOP_GetAttr(o, aHidd_BitMap_Height, &height);
        OOP_GetAttr(o, aHidd_BitMap_PixFmt, (IPTR *)&pf);
        OOP_GetAttr(pf, aHidd_PixFmt_Depth, &depth);

        ASSERT(
            (modeid != vHidd_ModeID_Invalid) &&
            (width != 0) && (height != 0) &&
            (depth != 0)
        );
        /* 
            We must only create depths that are supported by the friend drawable
            Currently we only support the default depth
        */

        width = (width + 15) & ~15;
        data->width = width;
        data->height = height;
        data->bpp = depth;
        data->disp = -1;

        data->bytesperpix = 1;
        if (depth > 24)
            data->bytesperpix = 4;
        else if (depth > 16)
            data->bytesperpix = 3;
        else if (depth > 8)
            data->bytesperpix = 2;

        data->data = &XSD(cl)->data;
        data->mouse = &XSD(cl)->mouse;

/*            RawPutChar(0x03);

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[1] = VCTAG_REQ;

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[2] = VCTAG_SETRES;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[3] = 8;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[4] = 8;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[5] = data->width;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[6] = data->height;

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[7] = VCTAG_SETVRES;      // duplicate physical size...
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[8] = 8;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[9] = 8;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[10] = data->width;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[11] = data->height;

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[12] = VCTAG_SETDEPTH;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[13] = 4;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[14] = 4;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[15] = data->bpp;

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[16] = VCTAG_FBALLOC;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[17] = 8;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[18] = 4;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[19] = 16;
            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[20] = 0;

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[21] = 0;                 // terminate tags

            (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[0] = (22 << 2);          // fill in request size

            VCMBoxWrite(VCMB_BASE, VCMB_FBCHAN, (unsigned int)(&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage);
            if ((VCMBoxRead(VCMB_BASE, VCMB_FBCHAN) == (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage)
                && ((&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[1] == VCTAG_RESP)
                && ((&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[18] == (VCTAG_RESP + 8)))
            {*/
                IPTR hardbuffer;
 //               hardbuffer = (&((struct VideoCoreGfxBase *)cl->UserData)->vsd)->vcsd_VCMBoxMessage[19];
                hardbuffer = AllocVec( data->width * data->height * data->bytesperpix, MEMF_PUBLIC);
                struct TagItem buffertags[] = {
                    { aHidd_ChunkyBM_Buffer, hardbuffer},
                    { TAG_DONE	     , 0    }
                };
                data->VideoData = buffertags[0].ti_Data;
                OOP_SetAttrs(o, buffertags);
                D(bug("[VideoCoreGfx] VideoCoreGfx.OnBitMap::New: FrameBuffer @ 0x%p\n", data->VideoData));

                int x,y;
                for (y = (data->height/2) - 10; y <(data->height/2) + 10; y++)
                {
                    for (x = (data->width/2) - 10; x <(data->width/2) + 10; x++)
                    {
                        void *p = data->VideoData + (y * (data->width * data->bytesperpix) + (x * data->bytesperpix));

                        switch (data->bytesperpix)
                        {
                        case 4:
                            *((int *)p) = 0x00FF0000;
                            break;

                        case 3:
                            /* qemu's truecolor modes are known to be 3 bytes per pixel */
                            *((short *)p) = 0x0000;
                            *((char *)p + 2) = 0xFF;
                            break;

                        case 2:
                            *((short *)p) = 0xF800;
                            break;

                        case 1:
                            *((char *)p) = 0xF0;
                            break;
                        }
                    }
                }

                ReturnPtr("VideoCoreGfx.OnBitMap::New: Obj", OOP_Object *, o);
/*
            }*/

        {
            OOP_MethodID disp_mid = OOP_GetMethodID(IID_Root, moRoot_Dispose);
            OOP_CoerceMethod(cl, o, (OOP_Msg) &disp_mid);
        }
        o = NULL;
    } /* if created object */
    ReturnPtr("VideoCoreGfx.OnBitMap::New: Obj", OOP_Object *, o);
}

/**********  Bitmap::Dispose()  ***********************************/

VOID MNAME_ROOT(Dispose)(OOP_Class *cl, OOP_Object *o, OOP_Msg msg)
{
    EnterFunc(bug("VideoCoreGfx.OnBitMap::Dispose()\n")); 
    OOP_DoSuperMethod(cl, o, msg);
    ReturnVoid("VideoCoreGfx.OnBitMap::Dispose");
}

VOID MNAME_BM(UpdateRect)(OOP_Class *cl, OOP_Object *o, struct pHidd_BitMap_UpdateRect *msg)
{
    struct BitmapData *data = OOP_INST_DATA(cl, o);

    D(bug("[VideoCoreGfx] VideoCoreGfx.OnBitMap::UpdateRect(%d, %d, %dx%d), bitmap 0x%p\n", msg->x, msg->y, msg->width, msg->height, o));
    if (data->disp) {
//	LOCK_FRAMEBUFFER(XSD(cl));
//        FNAME_HW(RefreshArea)(&XSD(cl)->data, data, msg->x, msg->y, msg->x + msg->width, msg->y + msg->height);
//	UNLOCK_FRAMEBUFFER(XSD(cl));
    }
}