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


#include <stdlib.h>

#include "nsmtracker.h"
#include "list_proc.h"
#include "trackreallines_proc.h"
#include "gfx_wtracks_proc.h"
#include "placement_proc.h"
#include "wtracks_proc.h"
#include "player_pause_proc.h"
#include "undo_notes_proc.h"
#include "cursor_updown_proc.h"
#include "blts_proc.h"
#include "playerclass.h"

#include "notes_proc.h"



extern struct Root *root;
extern PlayerClass *pc;


/**************************************************************
  FUNCTION
    Set the _end attributes for note 'note'.
**************************************************************/
void SetEndAttributes(
	struct Blocks *block,
	struct Tracks *track,
	struct Notes *note
){
	struct ListHeader3 *nextnote;
	struct ListHeader3 *stop;
	Place *place;
	Place *p1=NULL,*p2=NULL;

	nextnote=note->l.next;
	while(nextnote!=NULL){
		if(PlaceLessThan(&note->l.p,&nextnote->p)){
			p1= &nextnote->p;
			break;
		}
		nextnote=nextnote->next;
	}

	stop= &track->stops->l;
	while(stop!=NULL){
		if(PlaceLessThan(&note->l.p,&stop->p)){
			p2= &stop->p;
			break;
		}
		stop=stop->next;
	}

	place=PlaceMin(p1,p2);

	if(place!=NULL){
		note->end.line=place->line;
		note->end.counter=place->counter;
		note->end.dividor=place->dividor;
	}else{
		note->end.line=block->num_lines-1;
		note->end.counter=MAX_UINT32-1;
		note->end.dividor=MAX_UINT32;
		note->noend=1;
	}

}

/**************************************************************
  FUNCTION
    Stops all notes before line+(counter/dividor) at
    line+(counter/dividor, if they last that long.
**************************************************************/
void StopAllNotesAtPlace(
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	Place *placement
){
	struct Tracks *track=wtrack->track;
	struct Notes *temp;

/*
	if(wtrack->trackreallines[wblock->curr_realline].trackreallineelements==NULL)
		return;
*/

	temp=track->notes;

	while(PlaceLessThan(&temp->l.p,placement)){
		if(PlaceGreaterThan(&temp->end,placement)){
			CutListAt(&temp->velocities,placement);
			PlaceCopy(&temp->end,placement);
		}
		temp=NextNote(temp);
	}
}

void InsertNote(
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	Place *placement,
	int notenum,
	int velocity,
	int override
){
	struct Blocks *block=wblock->block;
	struct Tracks *track=wtrack->track;

	struct Notes *note=talloc(sizeof(struct Notes));

	PlaceCopy(&note->l.p,placement);

	note->note=notenum;
	note->velocity=velocity;
//	note->velocity=(*wtrack->track->instrument->getStandardVelocity)(wtrack->track);
	note->velocity_end=note->velocity;

	ListAddElement3(&track->notes,&note->l);

	if(override==0)
		StopAllNotesAtPlace(wblock,wtrack,placement);

	SetEndAttributes(block,track,note);

}


void InsertNoteCurrPos(struct Tracker_Windows *window,int notenum, int override){
	struct WBlocks *wblock;
	struct WTracks *wtrack;
	struct LocalZooms *realline;
	struct TrackReallineElements *element;
	struct Notes *note;
	struct Stops *stop;

	if(notenum<1 || notenum>127) return;

	PC_Pause();

	wblock=window->wblock;
	wtrack=wblock->wtrack;
	realline= wblock->reallines[wblock->curr_realline];

	Undo_Notes_CurrPos(window);

	if(
		0==override &&
		wtrack->trackreallines[wblock->curr_realline].note>0 &&
		wtrack->trackreallines[wblock->curr_realline].note<NOTE_MUL
	){
		wtrack->trackreallines[wblock->curr_realline].note=notenum;
		ClearTrack(window,wblock,wtrack,wblock->curr_realline,wblock->curr_realline);
		UpdateWTrack(window,wblock,wtrack,wblock->curr_realline,wblock->curr_realline);

		element=wtrack->trackreallines[wblock->curr_realline].trackreallineelements;
		while(element->type!=TRE_THISNOTELINES) element=element->next;
		note=(struct Notes *)element->pointer;
		note->note=notenum;

		if(window->curr_track_sub==-1 && !pc->isplaying){
			ScrollEditorDown(window,1);
		}

	}else{

		/* The following if-sentence is unecessarry, but it speeds up the responce
         time on slower machines a lot (extremly much actually).
		*/
	  /*
	    Removed. To much flicker.

		if(!wblock->isranged && wtrack->trackreallines[wblock->curr_realline].note==0){
			wtrack->trackreallines[wblock->curr_realline].note=notenum;
			UpdateWTrack(window,wblock,wtrack,wblock->curr_realline,wblock->curr_realline);
			Blt_blt(window);
		}
	  */
		stop=ListFindElement3(&wtrack->track->stops->l,&realline->l.p);
		if(stop!=NULL)
			if(PlaceEqual(&stop->l.p,&realline->l.p)){
				ListRemoveElement3(&wtrack->track->stops,&stop->l);
			}

		InsertNote(
			wblock,wtrack,&realline->l.p,notenum,
			wtrack->track->patch==NULL?root->standardvel:wtrack->track->patch->standardvel,
			override
		);

		if(wtrack->l.num==wblock->right_track && override!=0)
			UpdateAllWTracksCoordinates(window,wblock);

		if(window->curr_track_sub==-1 && override==0 && !pc->isplaying){
			ScrollEditorDown(window,1);
		}

		UpdateTrackReallines(window,wblock,wtrack);
		ClearTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
		UpdateWTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);

	}

	PC_StopPause();
}

void InsertStop(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	Place *placement
){
	struct Stops *stop;

	StopAllNotesAtPlace(wblock,wtrack,placement);

	stop=talloc(sizeof(struct Stops));
	PlaceCopy(&stop->l.p,placement);

	ListAddElement3(&wtrack->track->stops,&stop->l);

}

/**********************************************************************
  FUNCTION
    Set the end attributes of all notes that previously was stopped
    at position 'placement' to the next stop wherever that may be.
**********************************************************************/
void LengthenNotesTo(
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	Place *placement
){
	struct Notes *note=wtrack->track->notes;
	while(note!=NULL){
		if(PlaceGreaterThan(&note->l.p,placement)) break;
		if(PlaceEqual(&note->end,placement))
			SetEndAttributes(wblock->block,wtrack->track,note);
		note=NextNote(note);
	}
}

void RemoveNote(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	struct Notes *note
){
	struct LocalZooms *realline= wblock->reallines[wblock->curr_realline];

	ListRemoveElement3(&wtrack->track->notes,&note->l);

	LengthenNotesTo(wblock,wtrack,&realline->l.p);
}

void RemoveNoteCurrPos(struct Tracker_Windows *window){
	struct WBlocks *wblock;
	struct WTracks *wtrack;
	struct LocalZooms *realline;
	struct TrackReallineElements *element;
	struct TrackReallineElements *element2;
	struct Notes *note;
//	struct Notes *nextnote;

	PC_Pause();

	wblock=window->wblock;
	wtrack=wblock->wtrack;
	realline=wblock->reallines[wblock->curr_realline];

	Undo_Notes_CurrPos(window);

	if(
		wtrack->trackreallines[wblock->curr_realline].note!=0
	){

		element=wtrack->trackreallines[wblock->curr_realline].trackreallineelements;

		if(wtrack->trackreallines[wblock->curr_realline].note>=NOTE_MUL){
			element2=element;
			while(element2!=NULL){
				if(element2->type==TRE_STOPLINE)
					ListRemoveElement3(&wtrack->track->stops,(struct ListHeader3 *)element->pointer);
				element2=element2->next;
			}
		}

		while(element!=NULL){
			if(element->type==TRE_THISNOTELINES){
				note=(struct Notes *)element->pointer;
				ListRemoveElement3(&wtrack->track->notes,&note->l);
			}
			element=element->next;
//			nextnote=NextNote(note);
		}

		LengthenNotesTo(wblock,wtrack,&realline->l.p);

	}else{
		InsertStop(window,wblock,wtrack,&realline->l.p);
	}

	if(window->curr_track_sub==-1  && !pc->isplaying){
		ScrollEditorDown(window,1);
	}
	UpdateTrackReallines(window,wblock,wtrack);
	ClearTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
	UpdateWTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);

	PC_StopPause();

}


struct Notes *FindNoteOnSubTrack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int subtrack,
	int realline,
	Place *placement
){
	struct Notes *note;
	struct TrackRealline *trackrealline= &wtrack->trackreallines[realline];
	struct TrackReallineElements *element=trackrealline->trackreallineelements;

	while(element!=NULL){
		if(element->type==TRE_VELLINE && element->subtype==subtrack){
			note=(struct Notes *)element->pointer;
			if(PlaceIsBetween(placement,&note->l.p,&note->end)) return note;
		}
		element=element->next;
	}

	return NULL;
}

void StopVelocityCurrPos(struct Tracker_Windows *window,int noend){
	struct WBlocks *wblock;
	struct WTracks *wtrack;
	int reallinerealline;
	struct LocalZooms *realline;
	struct Notes *note;
	int subtrack;

	PC_Pause();

	wblock=window->wblock;
	wtrack=wblock->wtrack;
	reallinerealline=wblock->curr_realline;
	realline=wblock->reallines[reallinerealline];
	subtrack=window->curr_track_sub;

	Undo_Notes_CurrPos(window);

	note=FindNoteOnSubTrack(window,wblock,wtrack,subtrack,reallinerealline,&realline->l.p);
	if(note==NULL){
		PC_StopPause();
		return;
	}

	if(PlaceGreaterOrEqual(&note->l.p,&realline->l.p)){
		RemoveNote(window,wblock,wtrack,note);
	}else{
		CutListAt(&note->velocities,&realline->l.p);
		PlaceCopy(&note->end,&realline->l.p);
		note->noend=noend;
	}

	UpdateTrackReallines(window,wblock,wtrack);
	ClearTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
	UpdateWTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);

	PC_StopPause();

}
















