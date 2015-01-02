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
#include "list_proc.h"
#include "placement_proc.h"
#include "nodelines_proc.h"
#include "nodelines.h"
#include "gfx_wblocks_proc.h"
#include "time_proc.h"
#include "reltempo_proc.h"
#include "trackreallineelements_proc.h"
#include "undo_temponodes_proc.h"
#include <string.h>
#include "temponodes_legalize_proc.h"
#include "blackbox_proc.h"
#include "gfx_window_title_proc.h"
#include "player_proc.h"

#include "temponodes_proc.h"




void MakeWTempoNodesCallBack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	void *extrainfo,
	int firstlast,
	int realline,
	int u_y1,int u_y2,int u_x1,int u_x2
){
	struct TempoNodes *temponode=(struct TempoNodes *)extrainfo;
	WTempoNodes *wtemponode;

	GetTREelement(wtemponode);

	wtemponode->type=TEMPONODE_LINE;
	wtemponode->y1=u_y1;
	wtemponode->y2=u_y2;
	wtemponode->x1=u_x1;
	wtemponode->x2=u_x2;
	wtemponode->pointer=temponode;

	wtemponode->next=wblock->wtemponodes[realline];
	wblock->wtemponodes[realline]=wtemponode;

	if(firstlast==NODELINE_FIRST || firstlast==NODELINE_FIRSTANDLAST){
		GetTREelement(wtemponode);

		wtemponode->type=TEMPONODE_NODE;

		MakeBlackBox(window,u_x1,u_y1,wblock->temponodearea.width-1,wtemponode);

		wtemponode->pointer=temponode;
		wtemponode->next=wblock->wtemponodes[realline];
		wblock->wtemponodes[realline]=wtemponode;

	}

	if(NextTempoNode(temponode)==wblock->block->lasttemponode){
		if(firstlast==NODELINE_LAST || firstlast==NODELINE_FIRSTANDLAST){
			GetTREelement(wtemponode);
	
			wtemponode->type=TEMPONODE_NODE;

			MakeBlackBox(window,u_x2,u_y2,wblock->temponodearea.width-1,wtemponode);

			wtemponode->pointer=wblock->block->lasttemponode;
			wtemponode->next=wblock->wtemponodes[realline];
			wblock->wtemponodes[realline]=wtemponode;
		}
	}
}

void FreeAllWTempoNodes(
	struct WBlocks *wblock
){
	int lokke;
	if(wblock->wtemponodes==NULL) return;

	for(lokke=0;lokke<wblock->num_reallines_last;lokke++){
		FreeAllRTEelements_fromroot(
			&wblock->wtemponodes[lokke]
		);
	}

}

void UpdateWTempoNodes(
	struct Tracker_Windows *window,
	struct WBlocks *wblock
){
	struct TempoNodes *prev=wblock->block->temponodes;
	struct TempoNodes *temponode=NextTempoNode(prev);

	FreeAllWTempoNodes(wblock);
	if( wblock->num_reallines!=wblock->num_reallines_last || wblock->wtemponodes==NULL){
		wblock->wtemponodes=talloc_atomic(sizeof(WTempoNodes *) * wblock->num_reallines);
		memset(wblock->wtemponodes,0,wblock->num_reallines * sizeof(WTempoNodes *));
	}

	while(temponode!=NULL){
		MakeNodeLines(
			window,
			wblock,
			&prev->l.p,
			&temponode->l.p,
			prev->reltempo,
			temponode->reltempo,
			(float)(-wblock->reltempomax+1.0f),(float)(wblock->reltempomax-1.0f),
			1,wblock->temponodearea.width-1,
			prev,
			&MakeWTempoNodesCallBack
		);
		prev=temponode;
		temponode=NextTempoNode(temponode);
	}
}


void AddTempoNode(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	Place *p,
	float reltempo
){
	struct Blocks *block=wblock->block;
	struct TempoNodes *temponode;

	temponode=talloc(sizeof(struct TempoNodes));
	temponode->reltempo=reltempo;

	PlaceCopy(&temponode->l.p,p);

	if(ListAddElement3_ns(&block->temponodes,&temponode->l)==NULL)
		return;

}


void AddTempoNodeCurrPos(struct Tracker_Windows *window,float reltempo){
	struct WBlocks *wblock=window->wblock;

	PlayStop();

	Undo_TempoNodes_CurrPos(window);

	AddTempoNode(
		window,wblock,
		&wblock->reallines[wblock->curr_realline]->l.p,
		reltempo
	);

	UpdateWTempoNodes(window,wblock);
	DrawUpWTempoNodes(window,wblock);
	UpdateSTimes(wblock->block);

	GFX_DrawWindowTitle(window,wblock);
}

void RemoveAllTempoNodesOnReallineCurrPos(struct Tracker_Windows *window){
	struct WBlocks *wblock=window->wblock;
	WTempoNodes *wtemponode;
	int realline=wblock->curr_realline;

	PlayStop();

	Undo_TempoNodes_CurrPos(window);

	wtemponode=wblock->wtemponodes[realline];

	while(wtemponode!=NULL){
		if(wtemponode->type==TEMPONODE_NODE)
			ListRemoveElement3(&wblock->block->temponodes,(struct ListHeader3 *)wtemponode->pointer);
		wtemponode=wtemponode->next;
	}

	LegalizeTempoNodes(wblock->block);

	UpdateWTempoNodes(window,wblock);
	DrawUpWTempoNodes(window,wblock);
	UpdateSTimes(wblock->block);

	GFX_DrawWindowTitle(window,wblock);
}


float FindHighestTempoNodeVal(struct Blocks *block){
	struct TempoNodes *temponode=block->temponodes;

	float max=temponode->reltempo;
	temponode=NextTempoNode(temponode);

	while(temponode!=NULL){
		if(temponode->reltempo>max){
			max=temponode->reltempo;
		}
		temponode=NextTempoNode(temponode);
	}

	return max;
}


