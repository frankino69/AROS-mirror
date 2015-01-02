/* Copyright 2000 Kjetil S. Matheussen

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */


#include "nsmtracker.h"
#include "playerclass.h"
#include "PEQmempool_proc.h"
#include "OS_Ptask2Mtask_proc.h"
#include "PEQcommon_proc.h"
#include "realline_calc_proc.h"
#include "list_proc.h"

#include "PEQrealline_proc.h"



extern struct Root *root;

void PlayerNewRealline(STime time,struct PEventQueue *peq,int doit);

void InitPEQrealline(struct Blocks *block,Place *place){
	int addplaypos=0;
	int realline;
	struct WBlocks *wblock;
	struct Tracker_Windows *window=root->song->tracker_windows;
	struct PEventQueue *peq=NULL;

	while(window!=NULL){

		wblock=(struct WBlocks *)ListFindElement1(&window->wblocks->l,block->l.num);

		realline=FindRealLineFor(wblock,0,place);

		if(realline==0) realline++;		// Change or start of block is taken care of by PEQblock.c (and a block allways has at least two lines).

		if(realline>=wblock->num_reallines){
			realline=1;
			wblock=
				(struct WBlocks *)ListFindElement1(
				&window->wblocks->l,PC_GetPlayBlock(1)->l.num
			);
			addplaypos=1;
		}

		peq=GetPEQelement();
		peq->TreatMe=PlayerNewRealline;
		peq->window=window;
		peq->wblock=wblock;
		peq->realline=realline;

		PC_InsertElement2(
			peq, addplaypos,&wblock->reallines[realline]->l.p
		);
		Pdebug("time: %d, addplaypos: %d, realline: %d, wblocknum: %d\n",peq->l.time,addplaypos,realline,wblock->l.num);

		window=NextWindow(window);
	}
	debug("init. peq->realline: %d\n",peq->realline);
}


void PlayerNewRealline(STime time,struct PEventQueue *peq,int doit){
	int addplaypos=0;
	int realline=peq->realline;
//	int orgrealline=realline;
	struct Blocks *nextblock;

	peq->wblock->till_curr_realline=realline;

	if(doit){
		Ptask2Mtask();
	}

	realline++;

	if(realline>=peq->wblock->num_reallines){
		nextblock=PC_GetPlayBlock(1);
		if(nextblock==NULL){
			ReturnPEQelement(peq);
			return;
		}else{
			realline=1;
			peq->wblock=
				(struct WBlocks *)ListFindElement1(
				&peq->window->wblocks->l,nextblock->l.num
			);
			addplaypos=1;
		}
	}

	peq->realline=realline;

	PC_InsertElement2(
		peq, addplaypos ,&peq->wblock->reallines[realline]->l.p
	);

//	Pdebug("NewRealline: %d, time: %d, nextrealline: %d, nexttime: %d, addplaypos: %d, pc->seqtime: %d\n",orgrealline,time,peq->realline,peq->l.time,addplaypos,pc->seqtime);

	return;
}


