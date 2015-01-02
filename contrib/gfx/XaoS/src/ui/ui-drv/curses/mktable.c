
/* 
 *     XaoS, a fast portable realtime fractal zoomer 
 *                  Copyright (C) 1996,1997 by
 *
 *      Jan Hubicka          (hubicka@paru.cas.cz)
 *      Thomas Marsh         (tmarsh@austin.ibm.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include "mktable.h"
#include <config.h>
#ifdef CURSES_DRIVER
/* binary image of font8x8 follows */


static CONST unsigned char font8[] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 126, 129, 165, 129, 189, 129, 126, 0,		/* 0 to 15 */
  126, 255, 219, 255, 195, 255, 126, 0, 54, 127, 127, 127, 62, 28, 8, 0,	/* 16 to 31 */
  8, 28, 62, 127, 62, 28, 8, 0, 28, 28, 8, 107, 127, 107, 8, 28,	/* 32 to 47 */
  8, 28, 62, 127, 62, 8, 28, 62, 0, 0, 24, 60, 60, 24, 0, 0,	/* 48 to 63 */
  255, 255, 231, 195, 195, 231, 255, 255, 0, 60, 102, 66, 66, 102, 60, 0,	/* 64 to 79 */
  255, 195, 153, 189, 189, 153, 195, 255, 15, 7, 13, 60, 102, 102, 102, 60,	/* 80 to 95 */
  60, 102, 102, 102, 60, 24, 126, 24, 48, 56, 60, 54, 52, 112, 240, 224,	/* 96 to 111 */
  127, 99, 127, 99, 99, 103, 230, 192, 24, 219, 126, 102, 102, 126, 219, 24,	/* 112 to 127 */
  64, 112, 124, 127, 124, 112, 64, 0, 1, 7, 31, 127, 31, 7, 1, 0,	/* 128 to 143 */
  24, 60, 126, 24, 24, 126, 60, 24, 102, 102, 102, 102, 102, 0, 102, 0,		/* 144 to 159 */
  63, 122, 122, 58, 10, 10, 10, 0, 30, 51, 28, 54, 54, 28, 102, 60,	/* 160 to 175 */
  0, 0, 0, 0, 126, 126, 126, 0, 24, 60, 126, 24, 126, 60, 24, 126,	/* 176 to 191 */
  24, 60, 126, 24, 24, 24, 24, 0, 24, 24, 24, 24, 126, 60, 24, 0,	/* 192 to 207 */
  0, 12, 14, 127, 14, 12, 0, 0, 0, 24, 56, 127, 56, 24, 0, 0,	/* 208 to 223 */
  0, 0, 96, 96, 96, 127, 0, 0, 0, 36, 102, 255, 102, 36, 0, 0,	/* 224 to 239 */
  0, 24, 60, 126, 255, 255, 0, 0, 0, 255, 255, 126, 60, 24, 0, 0,	/* 240 to 255 */
  0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 24, 0, 24, 0,		/* 256 to 271 */
  102, 102, 102, 0, 0, 0, 0, 0, 108, 108, 254, 108, 254, 108, 108, 0,	/* 272 to 287 */
  16, 124, 208, 124, 22, 124, 16, 0, 0, 198, 204, 24, 48, 102, 198, 0,	/* 288 to 303 */
  56, 108, 56, 118, 220, 204, 118, 0, 24, 24, 48, 0, 0, 0, 0, 0,	/* 304 to 319 */
  12, 24, 48, 48, 48, 24, 12, 0, 48, 24, 12, 12, 12, 24, 48, 0,		/* 320 to 335 */
  0, 108, 56, 254, 56, 108, 0, 0, 0, 24, 24, 126, 24, 24, 0, 0,		/* 336 to 351 */
  0, 0, 0, 0, 0, 24, 24, 48, 0, 0, 0, 126, 0, 0, 0, 0,	/* 352 to 367 */
  0, 0, 0, 0, 0, 48, 48, 0, 0, 6, 12, 24, 48, 96, 192, 0,	/* 368 to 383 */
  60, 102, 110, 126, 118, 102, 60, 0, 12, 28, 60, 12, 12, 12, 12, 0,	/* 384 to 399 */
  60, 102, 6, 28, 48, 96, 126, 0, 60, 102, 6, 28, 6, 102, 60, 0,	/* 400 to 415 */
  28, 60, 108, 204, 254, 12, 12, 0, 126, 96, 96, 124, 6, 102, 60, 0,	/* 416 to 431 */
  60, 96, 96, 124, 102, 102, 60, 0, 126, 6, 6, 12, 24, 48, 48, 0,	/* 432 to 447 */
  60, 102, 102, 60, 102, 102, 60, 0, 60, 102, 102, 62, 6, 6, 60, 0,	/* 448 to 463 */
  0, 48, 48, 0, 0, 48, 48, 0, 0, 24, 24, 0, 0, 24, 24, 48,	/* 464 to 479 */
  12, 24, 48, 96, 48, 24, 12, 0, 0, 0, 126, 0, 0, 126, 0, 0,	/* 480 to 495 */
  48, 24, 12, 6, 12, 24, 48, 0, 60, 102, 6, 12, 24, 0, 24, 0,	/* 496 to 511 */
  60, 102, 110, 110, 108, 96, 60, 0, 24, 60, 102, 102, 126, 102, 102, 0,	/* 512 to 527 */
  124, 102, 102, 124, 102, 102, 124, 0, 60, 102, 96, 96, 96, 102, 60, 0,	/* 528 to 543 */
  124, 102, 102, 102, 102, 102, 124, 0, 126, 96, 96, 124, 96, 96, 126, 0,	/* 544 to 559 */
  126, 96, 96, 124, 96, 96, 96, 0, 60, 102, 96, 110, 102, 102, 60, 0,	/* 560 to 575 */
  102, 102, 102, 126, 102, 102, 102, 0, 60, 24, 24, 24, 24, 24, 60, 0,	/* 576 to 591 */
  6, 6, 6, 6, 102, 102, 60, 0, 102, 108, 120, 112, 120, 108, 102, 0,	/* 592 to 607 */
  96, 96, 96, 96, 96, 96, 126, 0, 198, 238, 254, 214, 198, 198, 198, 0,		/* 608 to 623 */
  102, 118, 126, 110, 102, 102, 102, 0, 60, 102, 102, 102, 102, 102, 60, 0,	/* 624 to 639 */
  124, 102, 102, 124, 96, 96, 96, 0, 60, 102, 102, 102, 102, 110, 60, 6,	/* 640 to 655 */
  124, 102, 102, 124, 102, 102, 102, 0, 60, 102, 96, 60, 6, 102, 60, 0,		/* 656 to 671 */
  126, 24, 24, 24, 24, 24, 24, 0, 102, 102, 102, 102, 102, 102, 60, 0,	/* 672 to 687 */
  102, 102, 102, 102, 102, 60, 24, 0, 198, 198, 198, 214, 254, 238, 198, 0,	/* 688 to 703 */
  102, 102, 60, 24, 60, 102, 102, 0, 102, 102, 102, 60, 24, 24, 24, 0,	/* 704 to 719 */
  126, 6, 12, 24, 48, 96, 126, 0, 60, 48, 48, 48, 48, 48, 60, 0,	/* 720 to 735 */
  0, 192, 96, 48, 24, 12, 6, 0, 60, 12, 12, 12, 12, 12, 60, 0,	/* 736 to 751 */
  24, 60, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255,		/* 752 to 767 */
  24, 24, 12, 0, 0, 0, 0, 0, 0, 0, 60, 6, 62, 102, 62, 0,	/* 768 to 783 */
  96, 96, 96, 124, 102, 102, 124, 0, 0, 0, 60, 102, 96, 102, 60, 0,	/* 784 to 799 */
  6, 6, 6, 62, 102, 102, 62, 0, 0, 0, 60, 102, 126, 96, 62, 0,	/* 800 to 815 */
  28, 54, 48, 124, 48, 48, 48, 0, 0, 0, 62, 102, 102, 62, 6, 60,	/* 816 to 831 */
  96, 96, 124, 102, 102, 102, 102, 0, 24, 0, 24, 24, 24, 24, 24, 0,	/* 832 to 847 */
  12, 0, 12, 12, 12, 12, 108, 56, 96, 96, 102, 108, 120, 108, 102, 0,	/* 848 to 863 */
  48, 48, 48, 48, 48, 48, 24, 0, 0, 0, 236, 254, 214, 214, 198, 0,	/* 864 to 879 */
  0, 0, 124, 102, 102, 102, 102, 0, 0, 0, 60, 102, 102, 102, 60, 0,	/* 880 to 895 */
  0, 0, 124, 102, 102, 124, 96, 96, 0, 0, 62, 102, 102, 62, 6, 6,	/* 896 to 911 */
  0, 0, 124, 102, 96, 96, 96, 0, 0, 0, 62, 96, 60, 6, 124, 0,	/* 912 to 927 */
  48, 48, 124, 48, 48, 54, 28, 0, 0, 0, 102, 102, 102, 102, 62, 0,	/* 928 to 943 */
  0, 0, 102, 102, 102, 60, 24, 0, 0, 0, 198, 214, 254, 238, 68, 0,	/* 944 to 959 */
  0, 0, 102, 60, 24, 60, 102, 0, 0, 0, 102, 102, 102, 62, 6, 60,	/* 960 to 975 */
  0, 0, 126, 12, 24, 48, 126, 0, 28, 48, 48, 96, 48, 48, 28, 0,		/* 976 to 991 */
  24, 24, 24, 24, 24, 24, 24, 0, 56, 12, 12, 6, 12, 12, 56, 0,	/* 992 to 1007 */
  118, 220, 0, 0, 0, 0, 0, 0, 0, 0, 24, 60, 102, 102, 126, 0,	/* 1008 to 1023 */
  60, 102, 96, 96, 102, 60, 24, 48, 102, 0, 102, 102, 102, 102, 62, 0,	/* 1024 to 1039 */
  14, 0, 60, 102, 126, 96, 60, 0, 60, 102, 60, 6, 62, 102, 62, 0,	/* 1040 to 1055 */
#ifdef __FULL_FONT
  102, 0, 60, 6, 62, 102, 62, 0, 112, 0, 60, 6, 62, 102, 62, 0,		/* 1056 to 1071 */
  24, 24, 60, 6, 62, 102, 62, 0, 0, 0, 62, 96, 96, 62, 24, 48,	/* 1072 to 1087 */
  60, 102, 60, 102, 126, 96, 60, 0, 102, 0, 60, 102, 126, 96, 60, 0,	/* 1088 to 1103 */
  112, 0, 60, 102, 126, 96, 60, 0, 102, 0, 24, 24, 24, 24, 24, 0,	/* 1104 to 1119 */
  60, 102, 24, 24, 24, 24, 24, 0, 112, 0, 24, 24, 24, 24, 24, 0,	/* 1120 to 1135 */
  198, 56, 108, 198, 254, 198, 198, 0, 24, 24, 0, 60, 102, 126, 102, 0,		/* 1136 to 1151 */
  14, 0, 124, 96, 120, 96, 124, 0, 0, 0, 126, 26, 126, 216, 126, 0,	/* 1152 to 1167 */
  62, 120, 216, 222, 248, 216, 222, 0, 60, 102, 60, 102, 102, 102, 60, 0,	/* 1168 to 1183 */
  102, 0, 60, 102, 102, 102, 60, 0, 112, 0, 60, 102, 102, 102, 60, 0,	/* 1184 to 1199 */
  60, 102, 0, 102, 102, 102, 62, 0, 112, 0, 102, 102, 102, 102, 62, 0,	/* 1200 to 1215 */
  102, 0, 102, 102, 102, 62, 6, 60, 102, 60, 102, 102, 102, 102, 60, 0,		/* 1216 to 1231 */
  102, 0, 102, 102, 102, 102, 60, 0, 12, 12, 62, 96, 96, 62, 12, 12,	/* 1232 to 1247 */
  56, 108, 96, 240, 96, 102, 252, 0, 102, 102, 60, 24, 126, 24, 126, 24,	/* 1248 to 1263 */
  124, 102, 102, 124, 102, 111, 102, 99, 14, 27, 24, 60, 24, 24, 120, 48,	/* 1264 to 1279 */
  14, 0, 60, 6, 62, 102, 62, 0, 14, 0, 24, 24, 24, 24, 24, 0,	/* 1280 to 1295 */
  14, 0, 60, 102, 102, 102, 60, 0, 14, 0, 102, 102, 102, 102, 62, 0,	/* 1296 to 1311 */
  118, 220, 0, 124, 102, 102, 102, 0, 126, 0, 102, 118, 126, 110, 102, 0,	/* 1312 to 1327 */
  62, 102, 102, 62, 0, 126, 0, 0, 60, 102, 102, 60, 0, 126, 0, 0,	/* 1328 to 1343 */
  24, 0, 24, 48, 96, 102, 60, 0, 0, 0, 0, 126, 96, 96, 0, 0,	/* 1344 to 1359 */
  0, 0, 0, 126, 6, 6, 0, 0, 198, 204, 216, 62, 99, 198, 12, 31,		/* 1360 to 1375 */
  198, 204, 216, 54, 110, 214, 31, 6, 24, 0, 24, 24, 24, 24, 24, 0,	/* 1376 to 1391 */
  0, 54, 108, 216, 108, 54, 0, 0, 0, 216, 108, 54, 108, 216, 0, 0,	/* 1392 to 1407 */
  34, 136, 34, 136, 34, 136, 34, 136, 85, 170, 85, 170, 85, 170, 85, 170,	/* 1408 to 1423 */
  221, 119, 221, 119, 221, 119, 221, 119, 8, 8, 8, 8, 8, 8, 8, 8,	/* 1424 to 1439 */
  8, 8, 8, 8, 248, 8, 8, 8, 8, 8, 8, 248, 248, 8, 8, 8,		/* 1440 to 1455 */
  28, 28, 28, 28, 252, 28, 28, 28, 0, 0, 0, 0, 252, 28, 28, 28,		/* 1456 to 1471 */
  0, 0, 0, 248, 248, 8, 8, 8, 28, 28, 28, 252, 252, 28, 28, 28,		/* 1472 to 1487 */
  28, 28, 28, 28, 28, 28, 28, 28, 0, 0, 0, 252, 252, 28, 28, 28,	/* 1488 to 1503 */
  28, 28, 28, 252, 252, 0, 0, 0, 28, 28, 28, 28, 252, 0, 0, 0,	/* 1504 to 1519 */
  8, 8, 8, 248, 248, 0, 0, 0, 0, 0, 0, 0, 248, 8, 8, 8,		/* 1520 to 1535 */
  8, 8, 8, 8, 15, 0, 0, 0, 8, 8, 8, 8, 255, 0, 0, 0,	/* 1536 to 1551 */
  0, 0, 0, 0, 255, 8, 8, 8, 8, 8, 8, 8, 15, 8, 8, 8,	/* 1552 to 1567 */
  0, 0, 0, 0, 255, 0, 0, 0, 8, 8, 8, 8, 255, 8, 8, 8,	/* 1568 to 1583 */
  8, 8, 8, 15, 15, 8, 8, 8, 28, 28, 28, 28, 31, 28, 28, 28,	/* 1584 to 1599 */
  28, 28, 28, 31, 31, 0, 0, 0, 0, 0, 0, 31, 31, 28, 28, 28,	/* 1600 to 1615 */
  28, 28, 28, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 28, 28, 28,		/* 1616 to 1631 */
  28, 28, 28, 31, 31, 28, 28, 28, 0, 0, 0, 255, 255, 0, 0, 0,	/* 1632 to 1647 */
  28, 28, 28, 255, 255, 28, 28, 28, 8, 8, 8, 255, 255, 0, 0, 0,		/* 1648 to 1663 */
  28, 28, 28, 28, 255, 0, 0, 0, 0, 0, 0, 255, 255, 8, 8, 8,	/* 1664 to 1679 */
  0, 0, 0, 0, 255, 28, 28, 28, 28, 28, 28, 28, 31, 0, 0, 0,	/* 1680 to 1695 */
  8, 8, 8, 15, 15, 0, 0, 0, 0, 0, 0, 15, 15, 8, 8, 8,	/* 1696 to 1711 */
  0, 0, 0, 0, 31, 28, 28, 28, 28, 28, 28, 28, 255, 28, 28, 28,	/* 1712 to 1727 */
  8, 8, 8, 255, 255, 8, 8, 8, 8, 8, 8, 8, 248, 0, 0, 0,		/* 1728 to 1743 */
  0, 0, 0, 0, 15, 8, 8, 8, 255, 255, 255, 255, 255, 255, 255, 255,	/* 1744 to 1759 */
  0, 0, 0, 0, 255, 255, 255, 255, 240, 240, 240, 240, 240, 240, 240, 240,	/* 1760 to 1775 */
  15, 15, 15, 15, 15, 15, 15, 15, 255, 255, 255, 255, 0, 0, 0, 0,	/* 1776 to 1791 */
  0, 0, 118, 204, 204, 204, 118, 0, 60, 102, 102, 124, 102, 102, 124, 96,	/* 1792 to 1807 */
  126, 102, 96, 96, 96, 96, 96, 0, 0, 0, 254, 108, 108, 108, 102, 0,	/* 1808 to 1823 */
  126, 102, 48, 24, 48, 102, 126, 0, 0, 0, 62, 108, 108, 108, 56, 0,	/* 1824 to 1839 */
  0, 0, 102, 102, 102, 102, 127, 192, 0, 0, 126, 216, 24, 24, 12, 0,	/* 1840 to 1855 */
  124, 56, 124, 214, 214, 124, 56, 124, 124, 198, 198, 254, 198, 198, 124, 0,	/* 1856 to 1871 */
  124, 198, 198, 198, 108, 108, 238, 0, 30, 48, 24, 60, 102, 102, 60, 0,	/* 1872 to 1887 */
  0, 0, 126, 219, 219, 126, 0, 0, 3, 6, 62, 107, 115, 62, 96, 192,	/* 1888 to 1903 */
  30, 48, 96, 126, 96, 48, 30, 0, 124, 198, 198, 198, 198, 198, 198, 0,		/* 1904 to 1919 */
  0, 126, 0, 126, 0, 126, 0, 0, 24, 24, 126, 24, 24, 0, 126, 0,		/* 1920 to 1935 */
  48, 24, 12, 24, 48, 0, 126, 0, 12, 24, 48, 24, 12, 0, 126, 0,		/* 1936 to 1951 */
  14, 27, 27, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 216, 216, 112,	/* 1952 to 1967 */
  24, 24, 0, 126, 0, 24, 24, 0, 0, 118, 220, 0, 118, 220, 0, 0,		/* 1968 to 1983 */
  60, 102, 102, 60, 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0,	/* 1984 to 1999 */
  0, 0, 0, 0, 24, 0, 0, 0, 30, 24, 24, 24, 24, 216, 120, 56,	/* 2000 to 2015 */
  120, 108, 108, 108, 108, 0, 0, 0, 56, 12, 24, 48, 60, 0, 0, 0,	/* 2016 to 2031 */
  0, 0, 60, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	/* 2032 to 2047 */
#endif
};

/* binary image of font8x16 follows */

static unsigned CONST char font16[] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 129,
  165, 129, 129, 189, 153, 129, 129, 126, 0, 0, 0, 0, 0, 0, 126, 255, 219, 255, 255, 195,
  231, 255, 255, 126, 0, 0, 0, 0, 0, 0, 0, 0, 108, 254, 254, 254, 254, 124, 56, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 16, 56, 124, 254, 124, 56, 16, 0, 0, 0, 0, 0,
  0, 0, 0, 24, 60, 60, 231, 231, 231, 24, 24, 60, 0, 0, 0, 0, 0, 0, 0, 24,
  60, 126, 255, 255, 126, 24, 24, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 60,
  60, 24, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 231, 195, 195, 231, 255, 255,
  255, 255, 255, 255, 0, 0, 0, 0, 0, 60, 102, 66, 66, 102, 60, 0, 0, 0, 0, 0,
  255, 255, 255, 255, 255, 195, 153, 189, 189, 153, 195, 255, 255, 255, 255, 255, 0, 0, 30, 14,
  26, 50, 120, 204, 204, 204, 204, 120, 0, 0, 0, 0, 0, 0, 60, 102, 102, 102, 102, 60,
24, 126, 24, 24, 0, 0, 0, 0, 0, 0, 63, 51, 63, 48, 48, 48, 48, 112, 240, 224,
0, 0, 0, 0, 0, 0, 127, 99, 127, 99, 99, 99, 99, 103, 231, 230, 192, 0, 0, 0,
0, 0, 0, 24, 24, 219, 60, 231, 60, 219, 24, 24, 0, 0, 0, 0, 0, 128, 192, 224,
  240, 248, 254, 248, 240, 224, 192, 128, 0, 0, 0, 0, 0, 2, 6, 14, 30, 62, 254, 62,
  30, 14, 6, 2, 0, 0, 0, 0, 0, 0, 24, 60, 126, 24, 24, 24, 126, 60, 24, 0,
0, 0, 0, 0, 0, 0, 102, 102, 102, 102, 102, 102, 102, 0, 102, 102, 0, 0, 0, 0,
  0, 0, 127, 219, 219, 219, 123, 27, 27, 27, 27, 27, 0, 0, 0, 0, 0, 124, 198, 96,
  56, 108, 198, 198, 108, 56, 12, 198, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  254, 254, 254, 254, 0, 0, 0, 0, 0, 0, 24, 60, 126, 24, 24, 24, 126, 60, 24, 126,
  0, 0, 0, 0, 0, 0, 24, 60, 126, 24, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0,
  0, 0, 24, 24, 24, 24, 24, 24, 24, 126, 60, 24, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 24, 12, 254, 12, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 96, 254,
  96, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 192, 192, 254, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 102, 255, 102, 36, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 16, 56, 56, 124, 124, 254, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  254, 254, 124, 124, 56, 56, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 24, 24, 24, 0, 24, 24,
  0, 0, 0, 0, 0, 102, 102, 102, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 108, 108, 254, 108, 108, 108, 254, 108, 108, 0, 0, 0, 0, 24, 24, 124, 198,
  194, 192, 124, 6, 6, 134, 198, 124, 24, 24, 0, 0, 0, 0, 0, 0, 194, 198, 12, 24,
  48, 96, 198, 134, 0, 0, 0, 0, 0, 0, 56, 108, 108, 56, 118, 220, 204, 204, 204, 118,
  0, 0, 0, 0, 0, 48, 48, 48, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 12, 24, 48, 48, 48, 48, 48, 48, 24, 12, 0, 0, 0, 0, 0, 0, 48, 24,
  12, 12, 12, 12, 12, 12, 24, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 102, 60, 255,
  60, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 126, 24, 24, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 48, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 12, 24,
  48, 96, 192, 128, 0, 0, 0, 0, 0, 0, 124, 198, 198, 206, 222, 246, 230, 198, 198, 124,
  0, 0, 0, 0, 0, 0, 24, 56, 120, 24, 24, 24, 24, 24, 24, 126, 0, 0, 0, 0,
0, 0, 124, 198, 6, 12, 24, 48, 96, 192, 198, 254, 0, 0, 0, 0, 0, 0, 124, 198,
  6, 6, 60, 6, 6, 6, 198, 124, 0, 0, 0, 0, 0, 0, 12, 28, 60, 108, 204, 254,
12, 12, 12, 30, 0, 0, 0, 0, 0, 0, 254, 192, 192, 192, 252, 6, 6, 6, 198, 124,
0, 0, 0, 0, 0, 0, 56, 96, 192, 192, 252, 198, 198, 198, 198, 124, 0, 0, 0, 0,
  0, 0, 254, 198, 6, 6, 12, 24, 48, 48, 48, 48, 0, 0, 0, 0, 0, 0, 124, 198,
  198, 198, 124, 198, 198, 198, 198, 124, 0, 0, 0, 0, 0, 0, 124, 198, 198, 198, 126, 6,
  6, 6, 12, 120, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 24, 24, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 24, 24, 48, 0, 0, 0, 0,
  0, 0, 0, 6, 12, 24, 48, 96, 48, 24, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 126, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 48, 24, 12, 6,
  12, 24, 48, 96, 0, 0, 0, 0, 0, 0, 124, 198, 198, 12, 24, 24, 24, 0, 24, 24,
  0, 0, 0, 0, 0, 0, 124, 198, 198, 198, 222, 222, 222, 220, 192, 124, 0, 0, 0, 0,
  0, 0, 16, 56, 108, 198, 198, 254, 198, 198, 198, 198, 0, 0, 0, 0, 0, 0, 252, 102,
  102, 102, 124, 102, 102, 102, 102, 252, 0, 0, 0, 0, 0, 0, 60, 102, 194, 192, 192, 192,
  192, 194, 102, 60, 0, 0, 0, 0, 0, 0, 248, 108, 102, 102, 102, 102, 102, 102, 108, 248,
0, 0, 0, 0, 0, 0, 254, 102, 98, 104, 120, 104, 96, 98, 102, 254, 0, 0, 0, 0,
  0, 0, 254, 102, 98, 104, 120, 104, 96, 96, 96, 240, 0, 0, 0, 0, 0, 0, 60, 102,
  194, 192, 192, 222, 198, 198, 102, 58, 0, 0, 0, 0, 0, 0, 198, 198, 198, 198, 254, 198,
198, 198, 198, 198, 0, 0, 0, 0, 0, 0, 60, 24, 24, 24, 24, 24, 24, 24, 24, 60,
  0, 0, 0, 0, 0, 0, 30, 12, 12, 12, 12, 12, 204, 204, 204, 120, 0, 0, 0, 0,
  0, 0, 230, 102, 102, 108, 120, 120, 108, 102, 102, 230, 0, 0, 0, 0, 0, 0, 240, 96,
  96, 96, 96, 96, 96, 98, 102, 254, 0, 0, 0, 0, 0, 0, 195, 231, 255, 255, 219, 195,
  195, 195, 195, 195, 0, 0, 0, 0, 0, 0, 198, 230, 246, 254, 222, 206, 198, 198, 198, 198,
  0, 0, 0, 0, 0, 0, 124, 198, 198, 198, 198, 198, 198, 198, 198, 124, 0, 0, 0, 0,
  0, 0, 252, 102, 102, 102, 124, 96, 96, 96, 96, 240, 0, 0, 0, 0, 0, 0, 124, 198,
  198, 198, 198, 198, 198, 214, 222, 124, 12, 14, 0, 0, 0, 0, 252, 102, 102, 102, 124, 108,
  102, 102, 102, 230, 0, 0, 0, 0, 0, 0, 124, 198, 198, 96, 56, 12, 6, 198, 198, 124,
  0, 0, 0, 0, 0, 0, 255, 219, 153, 24, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0,
  0, 0, 198, 198, 198, 198, 198, 198, 198, 198, 198, 124, 0, 0, 0, 0, 0, 0, 195, 195,
  195, 195, 195, 195, 195, 102, 60, 24, 0, 0, 0, 0, 0, 0, 195, 195, 195, 195, 195, 219,
  219, 255, 102, 102, 0, 0, 0, 0, 0, 0, 195, 195, 102, 60, 24, 24, 60, 102, 195, 195,
  0, 0, 0, 0, 0, 0, 195, 195, 195, 102, 60, 24, 24, 24, 24, 60, 0, 0, 0, 0,
0, 0, 255, 195, 134, 12, 24, 48, 96, 193, 195, 255, 0, 0, 0, 0, 0, 0, 60, 48,
48, 48, 48, 48, 48, 48, 48, 60, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 112, 56,
  28, 14, 6, 2, 0, 0, 0, 0, 0, 0, 60, 12, 12, 12, 12, 12, 12, 12, 12, 60,
  0, 0, 0, 0, 16, 56, 108, 198, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 48, 48, 24, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 12, 124,
  204, 204, 204, 118, 0, 0, 0, 0, 0, 0, 224, 96, 96, 120, 108, 102, 102, 102, 102, 124,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 198, 192, 192, 192, 198, 124, 0, 0, 0, 0,
  0, 0, 28, 12, 12, 60, 108, 204, 204, 204, 204, 118, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 124, 198, 254, 192, 192, 198, 124, 0, 0, 0, 0, 0, 0, 56, 108, 100, 96, 240, 96,
  96, 96, 96, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 204, 204, 204, 204, 204, 124,
  12, 204, 120, 0, 0, 0, 224, 96, 96, 108, 118, 102, 102, 102, 102, 230, 0, 0, 0, 0,
  0, 0, 24, 24, 0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 0, 0, 6, 6,
  0, 14, 6, 6, 6, 6, 6, 6, 102, 102, 60, 0, 0, 0, 224, 96, 96, 102, 108, 120,
120, 108, 102, 230, 0, 0, 0, 0, 0, 0, 56, 24, 24, 24, 24, 24, 24, 24, 24, 60,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 230, 255, 219, 219, 219, 219, 219, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 220, 102, 102, 102, 102, 102, 102, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 124, 198, 198, 198, 198, 198, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 220, 102, 102,
  102, 102, 102, 124, 96, 96, 240, 0, 0, 0, 0, 0, 0, 118, 204, 204, 204, 204, 204, 124,
  12, 12, 30, 0, 0, 0, 0, 0, 0, 220, 118, 102, 96, 96, 96, 240, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 124, 198, 96, 56, 12, 198, 124, 0, 0, 0, 0, 0, 0, 16, 48,
  48, 252, 48, 48, 48, 48, 54, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 204, 204,
  204, 204, 204, 118, 0, 0, 0, 0, 0, 0, 0, 0, 0, 195, 195, 195, 195, 102, 60, 24,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 195, 195, 195, 219, 219, 255, 102, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 195, 102, 60, 24, 60, 102, 195, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 198, 198, 198, 198, 198, 198, 126, 6, 12, 248, 0, 0, 0, 0, 0, 0, 254, 204, 24,
48, 96, 198, 254, 0, 0, 0, 0, 0, 0, 14, 24, 24, 24, 112, 24, 24, 24, 24, 14,
#ifdef __FULLFONT__
  0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 0, 24, 24, 24, 24, 24, 0, 0, 0, 0,
  0, 0, 112, 24, 24, 24, 14, 24, 24, 24, 24, 112, 0, 0, 0, 0, 0, 0, 118, 220,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 56, 108, 198,
  198, 198, 254, 0, 0, 0, 0, 0, 0, 0, 60, 102, 194, 192, 192, 192, 194, 102, 60, 12,
6, 124, 0, 0, 0, 0, 204, 0, 0, 204, 204, 204, 204, 204, 204, 118, 0, 0, 0, 0,
  0, 12, 24, 48, 0, 124, 198, 254, 192, 192, 198, 124, 0, 0, 0, 0, 0, 16, 56, 108,
  0, 120, 12, 124, 204, 204, 204, 118, 0, 0, 0, 0, 0, 0, 204, 0, 0, 120, 12, 124,
  204, 204, 204, 118, 0, 0, 0, 0, 0, 96, 48, 24, 0, 120, 12, 124, 204, 204, 204, 118,
0, 0, 0, 0, 0, 56, 108, 56, 0, 120, 12, 124, 204, 204, 204, 118, 0, 0, 0, 0,
  0, 0, 0, 0, 60, 102, 96, 96, 102, 60, 12, 6, 60, 0, 0, 0, 0, 16, 56, 108,
  0, 124, 198, 254, 192, 192, 198, 124, 0, 0, 0, 0, 0, 0, 198, 0, 0, 124, 198, 254,
  192, 192, 198, 124, 0, 0, 0, 0, 0, 96, 48, 24, 0, 124, 198, 254, 192, 192, 198, 124,
  0, 0, 0, 0, 0, 0, 102, 0, 0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0,
  0, 24, 60, 102, 0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 0, 96, 48, 24,
0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 0, 198, 0, 16, 56, 108, 198, 198,
  254, 198, 198, 198, 0, 0, 0, 0, 56, 108, 56, 0, 56, 108, 198, 198, 254, 198, 198, 198,
  0, 0, 0, 0, 24, 48, 96, 0, 254, 102, 96, 124, 96, 96, 102, 254, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 110, 59, 27, 126, 216, 220, 119, 0, 0, 0, 0, 0, 0, 62, 108,
  204, 204, 254, 204, 204, 204, 204, 206, 0, 0, 0, 0, 0, 16, 56, 108, 0, 124, 198, 198,
  198, 198, 198, 124, 0, 0, 0, 0, 0, 0, 198, 0, 0, 124, 198, 198, 198, 198, 198, 124,
0, 0, 0, 0, 0, 96, 48, 24, 0, 124, 198, 198, 198, 198, 198, 124, 0, 0, 0, 0,
  0, 48, 120, 204, 0, 204, 204, 204, 204, 204, 204, 118, 0, 0, 0, 0, 0, 96, 48, 24,
  0, 204, 204, 204, 204, 204, 204, 118, 0, 0, 0, 0, 0, 0, 198, 0, 0, 198, 198, 198,
  198, 198, 198, 126, 6, 12, 120, 0, 0, 198, 0, 124, 198, 198, 198, 198, 198, 198, 198, 124,
  0, 0, 0, 0, 0, 198, 0, 198, 198, 198, 198, 198, 198, 198, 198, 124, 0, 0, 0, 0,
  0, 24, 24, 126, 195, 192, 192, 192, 195, 126, 24, 24, 0, 0, 0, 0, 0, 56, 108, 100,
  96, 240, 96, 96, 96, 96, 230, 252, 0, 0, 0, 0, 0, 0, 195, 102, 60, 24, 255, 24,
  255, 24, 24, 24, 0, 0, 0, 0, 0, 252, 102, 102, 124, 98, 102, 111, 102, 102, 102, 243,
  0, 0, 0, 0, 0, 14, 27, 24, 24, 24, 126, 24, 24, 24, 24, 24, 216, 112, 0, 0,
  0, 24, 48, 96, 0, 120, 12, 124, 204, 204, 204, 118, 0, 0, 0, 0, 0, 12, 24, 48,
  0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 0, 24, 48, 96, 0, 124, 198, 198,
  198, 198, 198, 124, 0, 0, 0, 0, 0, 24, 48, 96, 0, 204, 204, 204, 204, 204, 204, 118,
0, 0, 0, 0, 0, 0, 118, 220, 0, 220, 102, 102, 102, 102, 102, 102, 0, 0, 0, 0,
  118, 220, 0, 198, 230, 246, 254, 222, 206, 198, 198, 198, 0, 0, 0, 0, 0, 60, 108, 108,
  62, 0, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 108, 108, 56, 0, 124, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 48, 0, 48, 48, 96, 192, 198, 198, 124,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 254, 192, 192, 192, 192, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 254, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 192, 192, 194,
  198, 204, 24, 48, 96, 206, 155, 6, 12, 31, 0, 0, 0, 192, 192, 194, 198, 204, 24, 48,
  102, 206, 150, 62, 6, 6, 0, 0, 0, 0, 24, 24, 0, 24, 24, 24, 60, 60, 60, 24,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 108, 216, 108, 54, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 216, 108, 54, 108, 216, 0, 0, 0, 0, 0, 0, 17, 68, 17, 68,
  17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 85, 170, 85, 170, 85, 170, 85, 170,
  85, 170, 85, 170, 85, 170, 85, 170, 221, 119, 221, 119, 221, 119, 221, 119, 221, 119, 221, 119,
  221, 119, 221, 119, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
  24, 24, 24, 24, 24, 24, 24, 248, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
  24, 248, 24, 248, 24, 24, 24, 24, 24, 24, 24, 24, 54, 54, 54, 54, 54, 54, 54, 246,
  54, 54, 54, 54, 54, 54, 54, 54, 0, 0, 0, 0, 0, 0, 0, 254, 54, 54, 54, 54,
54, 54, 54, 54, 0, 0, 0, 0, 0, 248, 24, 248, 24, 24, 24, 24, 24, 24, 24, 24,
  54, 54, 54, 54, 54, 246, 6, 246, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
  54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 0, 0, 0, 0, 0, 254, 6, 246,
54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 246, 6, 254, 0, 0, 0, 0,
  0, 0, 0, 0, 54, 54, 54, 54, 54, 54, 54, 254, 0, 0, 0, 0, 0, 0, 0, 0,
  24, 24, 24, 24, 24, 248, 24, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 248, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 31,
  0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 24, 24, 24, 255, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 24, 24, 24, 24, 24, 24, 24, 24,
  24, 24, 24, 24, 24, 24, 24, 31, 24, 24, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0,
  0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 24, 24, 24, 255,
  24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 31, 24, 31, 24, 24, 24, 24,
  24, 24, 24, 24, 54, 54, 54, 54, 54, 54, 54, 55, 54, 54, 54, 54, 54, 54, 54, 54,
  54, 54, 54, 54, 54, 55, 48, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 63, 48, 55, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 247, 0, 255,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 247, 54, 54, 54, 54,
  54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 48, 55, 54, 54, 54, 54, 54, 54, 54, 54,
  0, 0, 0, 0, 0, 255, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 54,
  54, 247, 0, 247, 54, 54, 54, 54, 54, 54, 54, 54, 24, 24, 24, 24, 24, 255, 0, 255,
  0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 54, 54, 54, 54, 54, 255, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 24, 24, 24, 24, 24, 24, 24, 24,
  0, 0, 0, 0, 0, 0, 0, 255, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
  54, 54, 54, 63, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 24, 31, 24, 31,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 24, 31, 24, 24, 24, 24,
  24, 24, 24, 24, 0, 0, 0, 0, 0, 0, 0, 63, 54, 54, 54, 54, 54, 54, 54, 54,
  54, 54, 54, 54, 54, 54, 54, 255, 54, 54, 54, 54, 54, 54, 54, 54, 24, 24, 24, 24,
  24, 255, 24, 255, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 248,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 24, 24, 24, 24,
  24, 24, 24, 24, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 240, 240, 240, 240,
  240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 220, 216, 216, 216, 220, 118, 0, 0, 0, 0,
  0, 0, 120, 204, 204, 204, 216, 204, 198, 198, 198, 204, 0, 0, 0, 0, 0, 0, 254, 198,
  198, 192, 192, 192, 192, 192, 192, 192, 0, 0, 0, 0, 0, 0, 0, 0, 254, 108, 108, 108,
  108, 108, 108, 108, 0, 0, 0, 0, 0, 0, 0, 254, 198, 96, 48, 24, 48, 96, 198, 254,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 126, 216, 216, 216, 216, 216, 112, 0, 0, 0, 0,
  0, 0, 0, 0, 102, 102, 102, 102, 102, 124, 96, 96, 192, 0, 0, 0, 0, 0, 0, 0,
118, 220, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0, 0, 0, 0, 126, 24, 60, 102, 102,
  102, 60, 24, 126, 0, 0, 0, 0, 0, 0, 0, 56, 108, 198, 198, 254, 198, 198, 108, 56,
  0, 0, 0, 0, 0, 0, 56, 108, 198, 198, 198, 108, 108, 108, 108, 238, 0, 0, 0, 0,
  0, 0, 30, 48, 24, 12, 62, 102, 102, 102, 102, 60, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 126, 219, 219, 219, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 126, 219, 219,
243, 126, 96, 192, 0, 0, 0, 0, 0, 0, 28, 48, 96, 96, 124, 96, 96, 96, 48, 28,
0, 0, 0, 0, 0, 0, 0, 124, 198, 198, 198, 198, 198, 198, 198, 198, 0, 0, 0, 0,
  0, 0, 0, 0, 254, 0, 0, 254, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  24, 24, 126, 24, 24, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 48, 24, 12, 6, 12,
  24, 48, 0, 126, 0, 0, 0, 0, 0, 0, 0, 12, 24, 48, 96, 48, 24, 12, 0, 126,
  0, 0, 0, 0, 0, 0, 14, 27, 27, 27, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
  24, 24, 24, 24, 24, 24, 24, 24, 216, 216, 216, 112, 0, 0, 0, 0, 0, 0, 0, 0,
  24, 24, 0, 126, 0, 24, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 220, 0,
  118, 220, 0, 0, 0, 0, 0, 0, 0, 56, 108, 108, 56, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 15, 12, 12,
  12, 12, 12, 236, 108, 108, 60, 28, 0, 0, 0, 0, 0, 216, 108, 108, 108, 108, 108, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 112, 216, 48, 96, 200, 248, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 124, 124, 124, 124, 124, 124, 124, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#endif
};
#define NPARAMS 5
#define NCHARS (128*NATTRS)
#define TABLESIZE 65536
struct parameters
  {
    unsigned char p[NPARAMS];
  };
static struct parameters *parameters;
unsigned short *table = NULL;
int supported[NATTRS] =
{1, 0, 1, 0, 0};
static unsigned short *next;
static int first = -1;
static int last = -1;
#define add(i) if(next[(i)]==(i)&&last!=(i)) {if(last!=-1) next[last]=(i),last=(i); else last=first=(i);}
#define dist(i1,i2,i3,i4,i5,y1,y2,y3,y4,y5) (3*(abs((int)(i1)-(int)(y1))+abs((int)(i2)-(int)(y2))+(abs((int)(i3)-(int)(y3))+abs((int)(i4)-(int)(y4))))+abs((int)(i5)-(int)(y5)))
#define pos(i1,i2,i3,i4) (((int)(i1)<<12)+((int)(i2)<<8)+((int)(i3)<<4)+(int)(i4))
#define postoparams(pos,i1,i2,i3,i4) \
  ((i1)=(pos)>>12),((i2)=((pos)>>8)&15),((i3)=((pos)>>4)&15),((i4)=((pos))&15)

#define isset(n,i) (((i)&1<<(n))!=0)
#define canset(n,i) (!isset(n,i)&&isset(n+1,i))
static int width = 8;
void 
values (int c, int *v1, int *v2, int *v3, int *v4)
{
  int i;
  int attr = c / 128;
  unsigned CONST char *font;
  if (width == 8)
    font = font8;
  else
    font = font16;
  c = c % 128;
  c = c * width;
  *v1 = 0;
  *v2 = 0;
  *v3 = 0;
  *v4 = 0;
  for (i = 0; i < width / 2; i++)
    {
      *v1 += (isset (0, font[c + i]) +
	      isset (1, font[c + i]) +
	      isset (2, font[c + i]) +
	      isset (3, font[c + i]));
      *v2 += (isset (4, font[c + i]) +
	      isset (5, font[c + i]) +
	      isset (6, font[c + i]) +
	      isset (7, font[c + i]));
    }
  for (; i < width; i++)
    {
      *v3 += (isset (0, font[c + i]) +
	      isset (1, font[c + i]) +
	      isset (2, font[c + i]) +
	      isset (3, font[c + i]));
      *v4 += (isset (4, font[c + i]) +
	      isset (5, font[c + i]) +
	      isset (6, font[c + i]) +
	      isset (7, font[c + i]));
    }
  switch (attr)
    {
    case REVERSE:
      *v1 = width * 2 - *v1;
      *v2 = width * 2 - *v2;
      *v3 = width * 2 - *v3;
      *v4 = width * 2 - *v4;
      break;
    case DIM:
      *v1 = (*v1 + 1) / 2;
      *v2 = (*v2 + 1) / 2;
      *v3 = (*v3 + 1) / 2;
      *v4 = (*v4 + 1) / 2;
      break;
    case BOLD:
      *v1 = *v1 * 2;
      *v2 = *v2 * 2;
      *v3 = *v3 * 2;
      *v4 = *v4 * 2;
      break;
    case BOLDFONT:
      for (i = 0; i < width / 2; i++)
	{
	  *v1 += (isset (0, font[c + i]) +
		  canset (1, font[c + i]) +
		  canset (2, font[c + i]) +
		  canset (3, font[c + i]));
	  *v2 += (isset (4, font[c + i]) +
		  canset (5, font[c + i]) +
		  canset (6, font[c + i]) +
		  canset (7, font[c + i]));
	}
      for (; i < width; i++)
	{
	  *v3 += (isset (0, font[c + i]) +
		  canset (1, font[c + i]) +
		  canset (2, font[c + i]) +
		  canset (3, font[c + i]));
	  *v4 += (isset (4, font[c + i]) +
		  canset (5, font[c + i]) +
		  canset (6, font[c + i]) +
		  canset (7, font[c + i]));
	}
    }
}
void static 
addparams (void)
{
  int i;
  int ma1 = 0, ma2 = 0, ma3 = 0, ma4 = 0, msum = 0;
  int mi1 = 50, mi2 = 50, mi3 = 50, mi4 = 50, misum = 50;
  int v1, v2, v3, v4, sum;
  for (i = 0; i < NCHARS; i++)
    {
      if ((!isgraph (i % 128) && (i % 128) != ' ') || !supported[i / 128])
	continue;
      values (i, &v1, &v2, &v3, &v4);
      if (v1 > ma1)
	ma1 = v1;
      if (v2 > ma2)
	ma2 = v2;
      if (v3 > ma3)
	ma3 = v3;
      if (v4 > ma4)
	ma4 = v4;
      if (v1 + v2 + v3 + v4 > msum)
	msum = v1 + v2 + v3 + v4;
      if (v1 < mi1)
	mi1 = v1;
      if (v2 < mi2)
	mi2 = v2;
      if (v3 < mi3)
	mi3 = v3;
      if (v4 < mi4)
	mi4 = v4;
      if (v1 + v2 + v3 + v4 < misum)
	misum = v1 + v2 + v3 + v4;
    }
  ma1 -= mi1;
  ma2 -= mi2;
  ma3 -= mi3;
  ma4 -= mi4;
  msum -= misum;
  for (i = 0; i < NCHARS; i++)
    {
      int pos;
      if ((!isgraph (i % 128) && (i % 128) != ' ') || !supported[i / 128])
	continue;
      values (i, &v1, &v2, &v3, &v4);
      sum = ((double) (v1 + v2 + v3 + v4 - misum) * (62.1 / (double) msum) + 0.900001);
      v1 = ((double) (v1 - mi1) * (14.1 / (double) ma1) + 0.9000001);
      v2 = ((double) (v2 - mi2) * (14.1 / (double) ma2) + 0.9000001);
      v3 = ((double) (v3 - mi3) * (14.1 / (double) ma3) + 0.9000001);
      v4 = ((double) (v4 - mi4) * (14.1 / (double) ma4) + 0.9000001);
      if (v1 > 15)
	v1 = 15;
      if (v2 > 15)
	v2 = 15;
      if (v3 > 15)
	v3 = 15;
      if (v4 > 15)
	v4 = 15;
      parameters[i].p[0] = v1;
      parameters[i].p[1] = v2;
      parameters[i].p[2] = v3;
      parameters[i].p[3] = v4;
      parameters[i].p[4] = sum;
      pos = pos (v1, v2, v3, v4);
      if (table[pos])
	{
	  if (abs ((parameters[i].p[4]) - v1 - v2 - v3 - v4) > abs (parameters[table[pos]].p[4] - v1 - v2 - v3 - v4))
	    continue;
	}
      table[pos] = i;

      add (pos);
    }
}
void 
mktable (void)
{
  int i;
  int i1, i2, i3, i4;
  next = (unsigned short *) malloc (sizeof (*next) * TABLESIZE);
  parameters = (struct parameters *) malloc (sizeof (struct parameters) * NCHARS);
  if (table == NULL)
    table = (unsigned short *) malloc (TABLESIZE * sizeof (*table));
  first = -1;
  last = -1;
  for (i = 0; i < TABLESIZE; i++)
    next[i] = i, table[i] = 0;
  addparams ();
  do
    {
      int blocked;
      if (last != -1)
	next[last] = last;
      else
	break;
      blocked = last;
      i = first;
      if (i == -1)
	break;
      first = last = -1;
      do
	{
	  int m1, m2, m3, m4, ii, dm;
	  unsigned short c = table[i];
	  /* printf ("%c\n", c); */
	  postoparams (i, m1, m2, m3, m4);
	  for (dm = 0; dm < 4; dm++)
	    for (ii = -1; ii <= 1; ii += 2)
	      {
		int dist, dist1, index;
		unsigned short ch;
		i1 = m1;
		i2 = m2;
		i3 = m3;
		i4 = m4;
		switch (dm)
		  {
		  case 0:
		    i1 += ii;
		    if (i1 < 0 || i1 >= 16)
		      continue;
		    break;
		  case 1:
		    i2 += ii;
		    if (i2 < 0 || i2 >= 16)
		      continue;
		    break;
		  case 2:
		    i3 += ii;
		    if (i3 < 0 || i3 >= 16)
		      continue;
		    break;
		  case 3:
		    i4 += ii;
		    if (i4 < 0 || i4 >= 16)
		      continue;
		    break;

		  }
		index = pos (i1, i2, i3, i4);
		ch = table[index];
		if (ch == c || index == blocked)
		  continue;
		if (ch)
		  {
		    int sum = i1 + i2 + i3 + i4;
		    dist = dist (
				  i1, i2, i3, i4, sum,
				  parameters[c].p[0],
				  parameters[c].p[1],
				  parameters[c].p[2],
				  parameters[c].p[3],
				  parameters[c].p[4]);
		    dist1 = dist (i1, i2, i3, i4, sum,
				  parameters[ch].p[0],
				  parameters[ch].p[1],
				  parameters[ch].p[2],
				  parameters[ch].p[3],
				  parameters[ch].p[4]);
		  }
		if (!ch || dist < dist1)
		  {
		    table[index] = c;
		    add (index);
		  }
	      }
	  i1 = i;
	  i = next[i];
	  next[i1] = i1;
	}
      while (i != i1);
    }
  while (last != -1);
  free ((void *) next);
  free ((void *) parameters);
}
void 
setheight (int i)
{
  width = i;
}

#endif
