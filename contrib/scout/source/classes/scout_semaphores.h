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
 * @author RiUBYTEd K�rber <rkoerber@gmx.de>
 */


/* Prototypes for functions defined in
objects/scout_semaphores.c
 */

struct SemaphoreEntry {
    struct MinNode se_Node;
    struct SignalSemaphore *se_Addr;
    TEXT se_Address[ADDRESS_LENGTH];
    TEXT se_Name[FILENAME_LENGTH];
    TEXT se_Pri[NUMBER_LENGTH];
    TEXT se_NestCount[NUMBER_LENGTH];
    TEXT se_QueueCount[NUMBER_LENGTH];
    TEXT se_Owner[NODENAME_LENGTH];
};

void PrintSemaphores( STRPTR );

void SendSemList( STRPTR );

#define SemaphoresWindowObject              NewObject(SemaphoresWinClass->mcc_Class, NULL

APTR MakeSemaphoresWinClass( void );

