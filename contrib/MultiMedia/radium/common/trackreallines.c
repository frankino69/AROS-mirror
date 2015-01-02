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




/*******************************************************************

   OVERVIEW

	Graphical datas for the notes and velocities. Not that elegant
	programmed as the fxlines and temponodelines, because it was
	programmed long before those ones.

*******************************************************************/


#include "nsmtracker.h"
#include <string.h>
#include "list_proc.h"
#include "localzooms_proc.h"
#include "windows_proc.h"
#include "wtracks_proc.h"
#include "subtrack_proc.h"
#include "placement_proc.h"
#include "realline_calc_proc.h"
#include "velocities_proc.h"
#include "gfx_subtrack_proc.h"
#include "nodelines_proc.h"
#include "nodelines.h"
#include "fxlines_proc.h"
#include "trackreallineelements_proc.h"

#include "trackreallines_proc.h"




struct TrackReallineNodeInfo{
	struct WTracks *wtrack;
	void *pointer;
	int type;
	int subtype;
};


void FreeAllRTEelements(
	struct WBlocks *wblock,
	struct WTracks *wtrack
){
	int lokke;
	struct TrackRealline *trackrealline;
	if(wtrack->trackreallines==NULL) return;

	for(lokke=0;lokke<wblock->num_reallines_last;lokke++){
		trackrealline= &wtrack->trackreallines[lokke];
		FreeAllRTEelements_fromroot(
			&trackrealline->trackreallineelements
		);
		trackrealline->note=0;
	}
}


/*******************************************************************
  FUNCTION
    This one both free old- and allocate new trackreallines.
*******************************************************************/
void NewTrackRealLines(
	struct WBlocks *wblock,
	struct WTracks *wtrack
){
	FreeAllRTEelements(wblock,wtrack);
	if( wblock->num_reallines!=wblock->num_reallines_last || wtrack->trackreallines==NULL){
		wtrack->trackreallines=talloc_atomic(wblock->num_reallines * sizeof(struct TrackRealline));
		memset(wtrack->trackreallines,0,wblock->num_reallines * sizeof(struct TrackRealline));
	}
}


static __inline void AddTrackReallineElement(
	struct WTracks *wtrack,
	struct TrackReallineElements *element,
	int realline
){
	element->next=wtrack->trackreallines[realline].trackreallineelements;
	wtrack->trackreallines[realline].trackreallineelements=element;
}


/**************************************************************************
  FUNCTION
    Adds a trackreallineelement to the trackline.
**************************************************************************/
static __inline void InsertTRLElementS(
	struct WTracks *wtrack,
	int realline,
	int type,int subtype,int y1,int y2,
	int x1,int x2,
	void *pointer
){
	struct TrackReallineElements *element;
	GetTREelement(element);
	element->next=NULL;
	element->type=type;
	element->subtype=subtype;
	element->y1=y1;
	element->y2=y2;
	element->x1=x1;
	element->x2=x2;
	element->pointer=pointer;

	AddTrackReallineElement(wtrack,element,realline);
}



struct TrackReallineElements *TRE_startroot=NULL;

static __inline void InsertTRLElement_start(
	struct TrackReallineElements *element,
	int realline
){
	element->type=realline;
	element->next=TRE_startroot;
	TRE_startroot=element;
}

void InsertStartTREElements(
	struct WTracks *wtrack
){
	struct TrackReallineElements *element=TRE_startroot,*temp;
	int realline;

	while(element!=NULL){
		temp=element->next;
		realline=element->type;
		element->type=TRE_REALSTARTSTOP;
		AddTrackReallineElement(wtrack,element,realline);	
		element=temp;
	}
	TRE_startroot=NULL;
}


/**************************************************************************
  FUNCTION
    Adds a trackreallineelement to the trackline. Does allso ensure that
    all datas are within the trackline area.
**************************************************************************/
static __inline void InsertTRLElement(
	struct Tracker_Windows *window,
	struct WTracks *wtrack,
	int subtrack,
	int realline,
	int type,int subtype,int y1,int y2,
	int x1,int x2,
	void *pointer
){
	struct TrackReallineElements *element;

	y1=min(window->fontheight,max(0,y1));
	y2=min(window->fontheight-1,max(0,y2));

	x1=SubtrackBoundaries(wtrack,subtrack,x1);
	x2=SubtrackBoundaries(wtrack,subtrack,x2);

	//	if(y1==y2 && x1==x2) return;
	
	GetTREelement(element);
	element->next=NULL;
	element->type=type;
	element->subtype=subtype;
	element->y1=y1;
	element->y2=y2;

	element->x1=x1;
	element->x2=x2;
	element->pointer=pointer;

	if(type==TRE_REALSTARTSTOP){
		InsertTRLElement_start(element,realline);
	}else{
		AddTrackReallineElement(wtrack,element,realline);
	}
}



/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
           Start of the AddTrackRealLineNote Part
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/**************************************************************************
  FUNCTION
    Adds a trackreallineelement to the trackline. Does allso ensure that
    all datas are within the trackline area.
**************************************************************************/
void NodeLineCallBack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	void *extrainfo,
	int firstlast,
	int realline,
	int y1,int y2,int x1,int x2
){
	struct TrackReallineNodeInfo *nodeinfo=(struct TrackReallineNodeInfo *)extrainfo;
	InsertTRLElementS(
		nodeinfo->wtrack,
		realline,
		nodeinfo->type,
		nodeinfo->subtype,
		y1,y2,x1,x2,
		nodeinfo->pointer
	);
}



void AddTrackReallineNote(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	struct Notes *note
){
	struct TrackReallineNodeInfo nodeinfo;

	int size=max(window->minnodesize,window->fontwidth/4);

	struct Velocities *velocity,*prev;
	int u_x1,u_y1,u_y1_start;

	int realline,realline_start;
	int subtrack;
	int startx,endx;


	float maxx=(float)(*wtrack->track->instrument->getMaxVelocity)(wtrack->track);

	int s_x1,s_x2;

	realline=FindRealLineForNote(wblock,note->Tline,note);
	subtrack=FindFirstFreeSubTrack(wtrack,realline,&note->l.p);
	startx=GetRelXSubTrack1(wtrack,subtrack);
	endx=GetRelXSubTrack2(wtrack,subtrack);

	InsertTRLElement(
		window,
		wtrack,
		subtrack,
		realline,
		TRE_THISNOTELINES,
		subtrack,
		0,0,0,0,					/* Will be filled in in the OrganizeThisNoteLines part. */
		note
	);

	u_y1=FindSubRealLine(window,wblock,realline,&note->l.p);

	u_x1=GetSubTrackPos(
		wtrack,
		(float) note->velocity,
		(int)maxx,
		subtrack
	);

	s_x1=u_x1-(2*window->fontwidth/3);
	s_x1=max(wtrack->fxwidth*subtrack/wtrack->num_vel+1,s_x1);
	s_x2=s_x1+(4*window->fontwidth/3);

	u_y1_start=u_y1;
	realline_start=realline;

	nodeinfo.wtrack=wtrack;
	nodeinfo.pointer=note;
	nodeinfo.type=TRE_VELLINE;
	nodeinfo.subtype=subtrack;

	velocity=note->velocities;
	if(velocity!=NULL){
		MakeNodeLines(
			window,
			wblock,
			&note->l.p,&velocity->l.p,
			(float)note->velocity,(float)velocity->velocity,
			0.0f,maxx,
			startx,endx,
			&nodeinfo,
			&NodeLineCallBack
		);
		prev=velocity;
		velocity=NextVelocity(velocity);
		while(velocity!=NULL){
			realline=FindRealLineFor(wblock,realline,&prev->l.p),
			u_y1=FindSubRealLine(window,wblock,realline,&prev->l.p);
			u_x1=GetSubTrackPos(wtrack,(float) prev->velocity,(int)maxx,subtrack);
			MakeNodeLines(
				window,
				wblock,
				&prev->l.p,&velocity->l.p,
				(float)prev->velocity,(float)velocity->velocity,
				0.0f,maxx,
				startx,endx,
				&nodeinfo,
				&NodeLineCallBack
			);
			InsertTRLElement(
				window,
				wtrack,
				subtrack,
				realline,
				TRE_VELLINENODE,
				subtrack,
				u_y1-size,u_y1+size,u_x1-size,u_x1+size,
				prev
			);
			prev=velocity;
			velocity=NextVelocity(velocity);
		}
		realline=FindRealLineFor(wblock,realline,&prev->l.p),
		u_y1=FindSubRealLine(window,wblock,realline,&prev->l.p);
		u_x1=GetSubTrackPos(wtrack,(float) prev->velocity,(int)maxx,subtrack);
		MakeNodeLines(
			window,
			wblock,
			&prev->l.p,&note->end,
			(float)prev->velocity,(float)note->velocity_end,
			0.0f,maxx,
			startx,endx,
			&nodeinfo,
			&NodeLineCallBack
		);
		InsertTRLElement(
			window,
			wtrack,
			subtrack,
			realline,
			TRE_VELLINENODE,
			subtrack,
			u_y1-size,u_y1+size,u_x1-size,u_x1+size,
			prev
		);
	}else{
		MakeNodeLines(
			window,
			wblock,
			&note->l.p,&note->end,
			(float)note->velocity,(float)note->velocity_end,
			0.0f,maxx,
			startx,endx,
			&nodeinfo,
			&NodeLineCallBack
		);
	}


	InsertTRLElement(
		window,
		wtrack,
		subtrack,
		realline_start,
		TRE_VELLINESTART,
		subtrack,
		u_y1_start-size,u_y1_start+size,s_x1,s_x2,
		note
	);

	InsertTRLElement(
		window,
		wtrack,
		subtrack,
		realline_start,
		TRE_REALSTARTSTOP,
		subtrack,
		u_y1_start,u_y1_start,0,2000,
		note
	);


	if(
		note->noend==1 &&
		note->end.line==wblock->block->num_lines-1 &&
		note->end.counter==MAX_UINT32-1 &&
		note->end.dividor==MAX_UINT32
	)return;

	realline=FindRealLineForEndNote(wblock,realline,note);

	u_y1=FindSubRealLine(window,wblock,realline,&note->end);

	u_x1=GetSubTrackPos(
		wtrack,
		(float) note->velocity_end,
		(int)maxx,
		subtrack
	);

	s_x1=u_x1-(2*window->fontwidth/3);
	s_x1=max(wtrack->fxwidth*subtrack/wtrack->num_vel+1,s_x1);
	s_x2=s_x1+(4*window->fontwidth/3);

	InsertTRLElement(
		window,
		wtrack,
		subtrack,
		realline,
		TRE_VELLINEEND,
		subtrack,
		u_y1-size,u_y1+size,s_x1,s_x2,
		note
	);

	InsertTRLElement(
		window,
		wtrack,
		subtrack,
		realline,
		TRE_REALSTARTSTOP,
		subtrack,
		u_y1,u_y1,0,2000,
		note
	);

}

/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
           End of the AddTrackRealLineNote Part
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/



/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
	       Start of the OrganizeThisNoteLines part
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/*** NOTES ****************************************************************
    About the following two procedures: There might be bugs here! I'm not
    at all too shure if they allways function correct.
***************************************************************************/
int FindNumberOfNotesOnTrackRealline(struct TrackReallineElements *element){
	int ret=0;
	while(element!=NULL){
		if(element->type==TRE_THISNOTELINES) ret++;
		element=element->next;
	}
	return ret;
}


int FindNumberOfFreeReallinesDown(struct WBlocks *wblock,struct WTracks *wtrack,int realline){
	int done=0;
	int free=realline+1;
	while(0==done && free<wblock->num_reallines){
		done=FindNumberOfNotesOnTrackRealline(wtrack->trackreallines[free].trackreallineelements);
		free++;
	}
	return max(0,free-realline-2);  /* The use of 'max' is just a hack here 
	                                   I did to get it to work. I don't know
	                                   if this allways works as I haven't
	                                   thought this function thru. ...After
	                                   thinking a bit more, I think it is correct.*/
}

/*** END NOTES ****/


/************************************************************************
  FUNCTION
    Set x1,y1,x2,y2 values for the TRE_THISNOTELINES trackrealline
    element 'element'.
************************************************************************/
void InsertCoordinatesForThisNoteLines(
	struct Tracker_Windows *window,
	struct WTracks *wtrack,
	int realline,
	struct TrackReallineElements *element
){
	int velend=0;
	struct TrackReallineElements *temp=wtrack->trackreallines[realline].trackreallineelements;

   /****************************************************************
     First find a suitable TRE_VELLINE element related to this note.
	 ****************************************************************/
	for(;;){
		if(temp==NULL){
			RError("Error in function 'InsertCoordinatesForThisNoteLines' in file 'trackreallines.c'\n");
			temp=wtrack->trackreallines[realline].trackreallineelements;
			break;
		}
		if(temp->pointer==element->pointer){
			if(temp->type==TRE_VELLINE &&
				(1==velend || (
					temp->y2 >= window->fontheight/2 &&
					temp->y1 <= window->fontheight/2
			)))break;

			if(
				0==velend &&
				(temp->type==TRE_VELLINEEND || temp->type==TRE_VELLINESTART)
			){
				temp=wtrack->trackreallines[realline].trackreallineelements;
				velend=1;
				continue;
			}
		}
		temp=temp->next;
	}


   /****************************************************************
	  Then use the coordinates for that TRE_VELLINE element to
	  calculate the coordinates for the TRE_THISNOTELINES element.
	 ****************************************************************/
	element->x1=0;
	element->y1=window->fontheight/2;

	element->x2=(temp->x1+temp->x2)/2-1;
	element->y2=(temp->y1+temp->y2)/2;

	element->subtype=0;

	wtrack->trackreallines[realline].note=((struct Notes *)(element->pointer))->note;
}


int NoteReachesDownToRealline(
	struct WBlocks *wblock,
	struct Notes *note,
	int realline
){
	struct LocalZooms *myrealline=wblock->reallines[realline];
	float a1=GetfloatFromLineCounterDividor(&myrealline->l.p);
	float a2=GetfloatFromLineCounterDividor(&note->end);

	if(a2>a1) return 1;
	return 0;
}


/****************************************************************
  FUNCTION
    Spread 'to_insert' number of notes placed on the realline to reallines
    below.  From the AddTrackReallineNote procedure, the latest note
    is put first and the first note is placed latest in the list,
    which makes the function relatively simple. The function does
    not work that good, and I have to admit I don't quite understand
    how it works any longer either, so it should be replaced with a new
    routine.
****************************************************************/
void InsertNotesFromRealline(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int realline,
	int to_insert,
	int of_notes
){
	struct TrackReallineElements *mylist=NULL;
	struct TrackReallineElements *element=wtrack->trackreallines[realline].trackreallineelements;
	struct TrackReallineElements *prev=NULL;
	int lokke;
	int mul=0;

	/* First handle as many elements as there are free lines down. This
	   is done by removing all such elements from the list and temporarily
	   put it in the new list 'mylist'.
	*/
	for(lokke=1;lokke<=to_insert;lokke++){

		/* Find element. */
		while(element->type!=TRE_THISNOTELINES){
			prev=element;
			element=element->next;
		}

		/* Temporarily remove it from the list */
		if(prev!=NULL){
			prev->next=element->next;
		}else{
			wtrack->trackreallines[realline].trackreallineelements=element->next;
		}

		/* Handle it. */
		if(
			NoteReachesDownToRealline(
				wblock,
				(struct Notes *)element->pointer,
				realline+to_insert-lokke+1
			)==1
		){
			AddTrackReallineElement(wtrack,element,realline+to_insert-lokke+1);
			InsertCoordinatesForThisNoteLines(window,wtrack,realline+to_insert-lokke+1,element);
		}else{
			element->next=mylist;
			mylist=element;
			InsertCoordinatesForThisNoteLines(window,wtrack,realline,element);
			mul=1;
		}

		/* Insert the element into the list again if it was okey. */
		if(prev!=NULL){
			element=prev->next;
		}else{
			element=wtrack->trackreallines[realline].trackreallineelements;
		}
	}


	/* Then handle the elements that has to be placed on the realline. */

	element=wtrack->trackreallines[realline].trackreallineelements;
	if(of_notes>to_insert+1){
		while(element!=NULL){
			while(element!=NULL && element->type!=TRE_THISNOTELINES) element=element->next;
			if(element!=NULL){
				InsertCoordinatesForThisNoteLines(window,wtrack,realline,element);
				element=element->next;
			}
		}
		mul=1;
	}else{
		while(element->type!=TRE_THISNOTELINES) element=element->next;
		wtrack->trackreallines[realline].note=((struct Notes *)(element->pointer))->note;
		InsertCoordinatesForThisNoteLines(window,wtrack,realline,element);
	}


	/* Now inserting the mylists elements back into the trackreallineelements list. */


	element=wtrack->trackreallines[realline].trackreallineelements;
	while(element->next!=NULL)element=element->next;
	element->next=mylist;


	/* Set note to NOTE_MUL if mul. */

	if(1==mul){
		wtrack->trackreallines[realline].note=NOTE_MUL;
	}


}

/****************************************************************
  FUNCTION
    Organizes the TRE_THISNOTELINES TRLEElements.
    Does ao. set the trackreallines->note attributes.
****************************************************************/
void OrganizeThisNoteLines(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack
){
	int lokke;
	int num_notes,num_freereallinesdown;
	struct TrackRealline *trackreallines=wtrack->trackreallines;
	struct Notes *note;
	struct TrackReallineElements *temp;

	for(lokke=0;lokke<wblock->num_reallines;lokke++){
		num_notes=FindNumberOfNotesOnTrackRealline(trackreallines[lokke].trackreallineelements);
		if(num_notes>0){
			if(num_notes>1){
				num_freereallinesdown=FindNumberOfFreeReallinesDown(wblock,wtrack,lokke);
				if(num_freereallinesdown>=num_notes-1){
					InsertNotesFromRealline(window,wblock,wtrack,lokke,num_notes-1,num_notes);
				}else{
					InsertNotesFromRealline(window,wblock,wtrack,lokke,num_freereallinesdown,num_notes);
				}
				lokke+=num_freereallinesdown;
			}else{
				temp=wtrack->trackreallines[lokke].trackreallineelements;
				while(temp->type!=TRE_THISNOTELINES) temp=temp->next;
				note=temp->pointer;
				trackreallines[lokke].note=note->note;
				InsertCoordinatesForThisNoteLines(window,wtrack,lokke,temp);
			}
		}
	}
}



/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
	       End of the OrganizeThisNoteLines part
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


void AddStopsElements(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack
){
	int realline=0;
	int subrealline;
	struct Stops *stop=wtrack->track->stops;

	while(stop!=NULL){
		realline=FindRealLineFor(wblock,max(stop->Tline,realline),&stop->l.p);

		subrealline=FindSubRealLine(window,wblock,realline,&stop->l.p);
		InsertTRLElementS(
			wtrack,
			realline,
			TRE_STOPLINE,0,
			subrealline,subrealline,0,wtrack->fxwidth-2,
			stop
		);

		if(wtrack->trackreallines[realline].note!=0){
			wtrack->trackreallines[realline].note=NOTE_MUL;
		}else{
			wtrack->trackreallines[realline].note=NOTE_STP;
		}
		stop=NextStop(stop);
	}

}

/****************************************************************
  FUNCTION
    Building up all from the ground, is what really happens.
****************************************************************/
void UpdateTrackReallines(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack
){
	struct Notes *note=wtrack->track->notes;

	SetNum_Vel(wtrack);

	/*
	if(wtrack->num_vel>(wtrack->fxwidth/(window->fontwidth*2))){
		wtrack->fxwidth=window->fontwidth*wtrack->num_vel*2;
		if(window->wblock==wblock){
			UpdateAllWTracksCoordinates(window,wblock);
			UpdateFXNodeLines(window,wblock,wtrack);
			DrawUpTrackerWindow(window);
		}
	}
	*/

	NewTrackRealLines(wblock,wtrack);

	while(note!=NULL){
		AddTrackReallineNote(window,wblock,wtrack,note);
		note=NextNote(note);
	}
	InsertStartTREElements(wtrack);

	OrganizeThisNoteLines(window,wblock,wtrack);

	AddStopsElements(window,wblock,wtrack);

	if(window->curr_track==wtrack->l.num)
		if(window->curr_track_sub >= wtrack->num_vel)
			window->curr_track_sub=wtrack->num_vel-1;

}


void UpdateAllTrackReallines(
	struct Tracker_Windows *window,
	struct WBlocks *wblock
){
	struct WTracks *wtrack=wblock->wtracks;

	while(wtrack!=NULL){
		UpdateTrackReallines(
			window,
			wblock,
			wtrack
		);
		wtrack=NextWTrack(wtrack);
	}
}


void UpdateSomeTrackReallines(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	NInt starttrack,
	NInt endtrack
){
	NInt lokke;

	struct WTracks *wtrack=ListFindElement1(&wblock->wtracks->l,starttrack);
	if(wtrack==NULL) return;

	for(lokke=0;lokke<=endtrack-starttrack;lokke++){
		UpdateTrackReallines(window,wblock,wtrack);
		wtrack=NextWTrack(wtrack);
		if(wtrack==NULL) break;
	}

}


/* The next one is used to speed up trackwidth changes.
   Should only be used when minimizing.
*/
void TR_scaleTrackReallines(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int oldwidth
	)
{
  struct TrackRealline *tr=wtrack->trackreallines;
  struct TrackReallineElements *tre;
  int num_reallines=wblock->num_reallines;
  int lokke;
  int width=wtrack->fxwidth;

  for(lokke=0;lokke<num_reallines;lokke++){
    tre=tr[lokke].trackreallineelements;
    while(tre!=NULL){
      tre->x1=(tre->x1*width)/oldwidth;
      tre->x2=(tre->x2*width)/oldwidth;
      tre=tre->next;
    }
  }

}






