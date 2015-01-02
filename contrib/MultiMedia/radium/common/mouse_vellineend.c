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
#include "common_proc.h"
#include "placement_proc.h"
#include "gfx_subtrack_proc.h"
#include "trackreallines_proc.h"
#include "gfx_wtracks_proc.h"
#include "undo_notes_proc.h"
#include "gfx_window_title_proc.h"
#include "player_proc.h"
#include "realline_calc_proc.h"

#include "mouse_vellineend_proc.h"




/* Everything needs to be drawn up if:
   1. wtrack->num_vel is changed, or
   2. wtrack->num_vel>1
*/

int MoveVelEnd_Mouse(
	struct Tracker_Windows *window,
	int x,int y
){
	struct WBlocks *wblock=window->wblock;
	struct MouseAction *action= &window->prevaction;
	struct WTracks *wtrack=(struct WTracks *)action->pointer1;
	struct Tracks *track=wtrack->track;
	struct Notes *note=(struct Notes *)action->pointer2;
	struct Notes *nextnote;
	struct Velocities *lastvelocity;
	int subtrack=action->eint1;
	Place place;
	Place *pp_vel,*pn_vel;
	int maxvel=(*track->instrument->getMaxVelocity)(track);
	int sx1=GetXSubTrack1(wtrack,subtrack);
	int sx2=GetXSubTrack2(wtrack,subtrack);
	int velocity_end_org=note->velocity_end;

	int num_vel;
	int start_realline,realline,end_realline;

	PlayStop();

	num_vel=wtrack->num_vel;

	nextnote=ListFindElement3(&note->l,&note->end);
	if(nextnote!=NULL){
		pn_vel= &nextnote->l.p;
	}else{
		pn_vel=NULL;
	}

	lastvelocity=(struct Velocities *)ListLast3(&note->velocities->l);
	if(lastvelocity==NULL){
		pp_vel= &note->l.p;
	}else{
		pp_vel= &lastvelocity->l.p;
	}
	start_realline=FindRealLineFor(wblock,0,pp_vel);
	end_realline=FindRealLineFor(wblock,0,&note->end);

	realline=GetReallineAndPlaceFromY(window,wblock,y,&place,pp_vel,pn_vel);

	note->velocity_end=(maxvel*(x-sx1)/(sx2-sx1));
	note->velocity_end=boundaries(0,note->velocity_end,maxvel);
	if(note->velocities==NULL && note->velocity==velocity_end_org){
		note->velocity=note->velocity_end;
	}

	PlaceCopy(&note->end,&place);

	UpdateTrackReallines(window,wblock,wtrack);

	if(num_vel>1 || num_vel!=wtrack->num_vel){
	  ClearTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
	  UpdateWTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
	}else{
	  start_realline=min(realline,start_realline);
	  end_realline=max(realline,end_realline);
	  ClearTrack(window,wblock,wtrack,start_realline,end_realline);
	  UpdateWTrack(window,wblock,wtrack,start_realline,end_realline);
	}

	GFX_SetChangeInt(window,wblock,"Velocity End",note->velocity_end);

	GFX_DrawWindowTitle(window,wblock);

	return 0;
}



void SetMouseActionVellineEnd(
	struct Tracker_Windows *window,
	struct MouseAction *action,
	struct WTracks *wtrack,
	struct Notes *note,
	int realline,
	int subtrack,
	int x,int y,
	int click
){
	action->action=NOTEEND;
	action->pointer1=wtrack;
	action->pointer2=note;
	action->eint1=subtrack;
	action->MouseUpFunction= &MoveVelEnd_Mouse;

	if(click==1){
		PlayStop();
		Undo_Notes(window,window->wblock->block,wtrack->track,window->wblock->curr_realline);
	}
}

