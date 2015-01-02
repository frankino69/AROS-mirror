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
#include "fxlines_proc.h"
#include "placement_proc.h"
#include "common_proc.h"
#include "gfx_wtracks_proc.h"
#include "undo_fxs_proc.h"
#include "gfx_window_title_proc.h"
#include "player_proc.h"
#include "realline_calc_proc.h"

#include "mouse_fxnode_proc.h"



int MoveFXNode_Mouse(
	struct Tracker_Windows *window,
	int x,int y
){
	struct WBlocks *wblock=window->wblock;
	struct MouseAction *action= &window->prevaction;
	struct WTracks *wtrack=(struct WTracks *)action->pointer1;
	struct Tracks *track=wtrack->track;
	struct FXs *fxs=(struct FXs *)action->pointer2;
	struct FXNodeLines *fxnodeline=(struct FXNodeLines *)action->pointer3;
	struct FXNodeLines *nextnodeline=NextFXNodeLine(fxnodeline);
	struct FXNodeLines *prevnodeline;
	struct FX *fx=fxs->fx;

	Place place;
	Place *pp,*pn;
	int realline;
	int sx1=wtrack->fxarea.x;
	int sx2=wtrack->fxarea.x2-1;

	int start_realline,end_realline;


	PlayStop();

	if(fxs->fxnodelines==fxnodeline){
		pp=NULL;
		start_realline=FindRealLineFor(wblock,0,&fxnodeline->l.p);
	}else{
		prevnodeline=(struct FXNodeLines *)ListPrevElement3(&fxs->fxnodelines->l,&fxnodeline->l);
		pp= &prevnodeline->l.p;
		start_realline=FindRealLineFor(wblock,0,pp);
	}
	if(nextnodeline==NULL){
		pn=NULL;
		end_realline=FindRealLineFor(wblock,start_realline,&fxnodeline->l.p);
	}else{
		pn= &nextnodeline->l.p;
		end_realline=FindRealLineFor(wblock,start_realline,pn);
	}

	realline=GetReallineAndPlaceFromY(window,wblock,y,&place,pp,pn);

	if(
		realline< -window->fontheight*3 ||
		x>sx2+window->fontwidth*3 ||
		x<sx1-window->fontwidth*3
	){
		ListRemoveElement3(&fxs->fxnodelines,&fxnodeline->l);
		if(ListFindNumElements3(&fxs->fxnodelines->l)<=1){
			(*fx->closeFX)(fx,track);
			ListRemoveElement1(&track->fxs,&fxs->l);
		}
		action->action=NOACTION;
	}else{
		PlaceCopy(&fxnodeline->l.p,&place);
		fxnodeline->val=((fx->max-fx->min)*(x-sx1)/(sx2-sx1))+fx->min;
		fxnodeline->val=boundaries(fx->min,fxnodeline->val,fx->max);
		GFX_SetChangeInt(window,wblock,fx->name,fxnodeline->val);
		GFX_DrawWindowTitle(window,wblock);

		start_realline=min(start_realline,realline);
		end_realline=max(end_realline,realline);
	}


	UpdateFXNodeLines(window,wblock,wtrack);

	ClearTrack(window,wblock,wtrack,
		   start_realline,
		   end_realline
		   );

	UpdateWTrack(window,wblock,wtrack,
		     start_realline,
		     end_realline
		     );

	return 0;
}

struct FXs *getFXs(
	struct Tracks *track,
	struct FXNodeLines *fxnodeline
){
	struct FXs *fxs=track->fxs;
	for(;;){
		if(isInList3(&fxs->fxnodelines->l,&fxnodeline->l)){
			return fxs;
		}
		fxs=NextFX(fxs);
	}
	RError("Error in function 'getFXS' in file 'mouse_fxnode.c'\n");
}

void SetMouseActionFXNode(
	struct Tracker_Windows *window,
	struct MouseAction *action,
	struct WTracks *wtrack,
	WFXNodes *wfxnode,
	int click
){
	struct Tracks *track=wtrack->track;
	struct FXs *fxs;
	struct FX *fx;
	struct FXNodeLines *fxnodeline;

	action->pointer1=wtrack;
	action->pointer3=wfxnode->pointer;

	fxnodeline=(struct FXNodeLines *)wfxnode->pointer;
	fxs=getFXs(track,fxnodeline);
	action->pointer2=fxs;
	action->action=FXNODE;
	action->MouseUpFunction= &MoveFXNode_Mouse;

	fx=fxs->fx;
	GFX_SetChangeInt(window,window->wblock,fx->name,fxnodeline->val);
	GFX_DrawWindowTitle(window,window->wblock);

	if(click==1){
		Undo_FXs(window,window->wblock->block,wtrack->track,window->wblock->curr_realline);
	}

}


