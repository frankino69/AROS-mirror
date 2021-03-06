//========================================================================
//
// rasterize_32.cc
//
// Copyright 2000-2001 Emmanuel Lesueur
//
//========================================================================

#include "rasterize.h"

typedef unsigned short Gushort;

void fill(ABitmap& bm, int x0, int y0, region* area, Gulong color) {
  _fill(bm, x0, y0, area, color);
}

void AAfill(ABitmap& bm, int x0, int y0, region* area,
	    Gulong c1, Gulong c2, Gulong c3, Gulong c4) {
  _AAfill(bm, x0, y0, area, c1, c2, c3, c4);
}

void rectfill(ABitmap& bm, int x0, int y0, int w, int h, Gulong color) {
  _rectfill(bm, x0, y0, w, h, color);
}

void clippedHLine(ABitmap& bm, int y, int x1, int x2, Gulong color, DashState& ds) {
  _clippedHLine(bm, y, x1, x2, color, ds);
}

void clippedVLine(ABitmap& bm, int x, int y1, int y2, Gulong color, DashState& ds) {
  _clippedVLine(bm, x, y1, y2, color, ds);
}

void clippedLine(ABitmap& bm, fractpel x1, fractpel y1, fractpel x2, fractpel y2, Gulong color, DashState& ds) {
  _clippedLine(bm, x1, y1, x2, y2, color, ds);
}

void clippedCopy(ABitmap& bm1, ABitmap& bm2, region* area) {
  _clippedCopy<4>(bm1, bm2, area);
}

void drawPicLine(AOutputDev::DrawPicParams& params, int y, int x1, int x2,
		 int xp1, int yp1, int xp2, int yp2) {
  _drawPicLine<Gulong>(params, y, x1, x2, xp1, yp1, xp2, yp2);
}

void (*funcTable[])() = {
  (void (*)())fill, (void (*)())AAfill, (void (*)())rectfill,
  (void (*)())clippedHLine, (void (*)())clippedVLine, (void (*)())clippedLine,
  (void (*)())clippedCopy, (void (*)())drawPicLine,
  NULL, NULL, NULL, NULL, NULL, NULL
};

#ifdef __PPC__
static const char verstring[]="$VER:ApdfGfx32_" PROC ".module 1.0 (27.12.2000)";
#else
extern const char LibName[];
extern const char LibId[];
const char LibName[]="ApdfGfx32_" PROC ".module";
const char LibId[]="ApdfGfx32_" PROC ".module 1.0 (27.12.2000)";
#endif

