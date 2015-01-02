/**
 * Scout - The Amiga System Monitor
 *
 *------------------------------------------------------------------
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *------------------------------------------------------------------
 *
 * @author Andreas Gelhausen
 * @author Richard K�rber <rkoerber@gmx.de>
 */


/* Prototypes for functions defined in
objects/scout_memory_detail.c
 */

struct MemoryFreeEntry {
    TEXT mfe_Lower[16];
    TEXT mfe_Upper[16];
    TEXT mfe_Size[24];
};

#if defined(__AROS__)
    #define MemoryDetailWindowObject  BOOPSIOBJMACRO_START(MemoryDetailWinClass->mcc_Class)
#else
    #define MemoryDetailWindowObject  NewObject(MemoryDetailWinClass->mcc_Class, NULL
#endif

APTR MakeMemoryDetailWinClass( void );

