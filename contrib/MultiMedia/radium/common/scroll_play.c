/* Copyright 2001 Kjetil S. Matheussen

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



/*
   Handles playing of notes while scrolling (ie. up down arrow, etc. )
   while not playing. (playing of fxes could be annoying; may be
   implemented later).
*/


#include "nsmtracker.h"
#include "playerclass.h"
#include "wblocks_proc.h"

#include "scroll_play_proc.h"



void Scroll_play_do(
	struct WBlocks *wblock,
	int realline
){
	struct WTracks *wtrack;
	struct Notes *note;
	struct Patch *patch;
	struct TrackReallineElements *tre;

	for(wtrack=wblock->wtrack;wtrack!=NULL;wtrack=NextWTrack(wtrack)){
		patch=wtrack->track->patch;
		if(patch==NULL || wtrack->track->onoff==0) continue;

		tre=wtrack->trackreallines[realline].trackreallineelements;

		while(tre!=NULL){
			if(tre->type==TRE_VELLINESTART){
				note=(struct Notes *)tre->pointer;
				(*patch->playnote)(note->note,note->velocity,wtrack->track,note);
			}
			if(tre->type==TRE_VELLINEEND){
				note=(struct Notes *)tre->pointer;
				(*patch->stopnote)(note->note,note->velocity_end,wtrack->track,note);
			}
			tre=tre->next;
		}
	}
}

void Scroll_play_down(
	struct WBlocks *wblock,
	int start_realline,
	int end_realline
){
	int lokke;

	for(lokke=start_realline;lokke<=end_realline;lokke++){
		Scroll_play_do(wblock,lokke);
	}
}

void Scroll_play_up(
	struct WBlocks *wblock,
	int start_realline,
	int end_realline
){
	int lokke;

	for(lokke=end_realline;lokke>=start_realline;lokke--){
		Scroll_play_do(wblock,lokke);
	}
}

extern PlayerClass *pc;
extern struct Root *root;

void Scroll_play(
	struct WBlocks *wblock,
	int start_realline,
	int end_realline
){
	if(pc->isplaying || root->scrollplayonoff==false) return;

	start_realline=boundaries(0,start_realline,wblock->num_reallines-1);
	end_realline=boundaries(0,end_realline,wblock->num_reallines-1);
	
//	printf("start: %d, end: %d\n",start_realline,end_realline);

	if(start_realline<=end_realline){
		Scroll_play_down(wblock,start_realline,end_realline);
	}
	if(start_realline>end_realline){
		Scroll_play_up(wblock,start_realline,end_realline);
	}
}




