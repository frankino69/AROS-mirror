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
objects/scout_resources_detail.c
 */

struct FileSystemEntry {
    struct MinNode fse_Node;
    char fse_FileSystem[NUMBER_LENGTH];
    char fse_DosType[NUMBER_LENGTH];
    char fse_Version[VERSION_LENGTH];
    char fse_PatchFlags[NUMBER_LENGTH];
    char fse_Creator[NODENAME_LENGTH];
};

#if defined(__AROS__)
    #define ResourcesDetailWindowObject  BOOPSIOBJMACRO_START(ResourcesDetailWinClass->mcc_Class)
#else
    #define ResourcesDetailWindowObject  NewObject(ResourcesDetailWinClass->mcc_Class, NULL
#endif

APTR MakeResourcesDetailWinClass( void );

