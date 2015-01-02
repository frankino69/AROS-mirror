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

#include "gfx_subtrack_proc.h"




/************************************************************************
  FUNCTION
    Returns the left X coordinate relative to track->fx.y for the subtrack
    'subtrack'.
************************************************************************/
int GetRelXSubTrack1(
	struct WTracks *wtrack,
	int subtrack
){
	return (wtrack->fxwidth*subtrack/wtrack->num_vel) + (subtrack>0 ? 1 : 0 ) ;
}

/************************************************************************
  FUNCTION
    Returns the absolute left X coordinate to track->fx.y for the subtrack
    'subtrack'.
************************************************************************/
int GetXSubTrack1(
	struct WTracks *wtrack,
	int subtrack
){
	if(subtrack==-1) return wtrack->notearea.x;
	return wtrack->fxarea.x + GetRelXSubTrack1(wtrack,subtrack);
}

/************************************************************************
  FUNCTION
    Returns the right X coordinate relative to track->fx.y for the subtrack
    'subtrack'.
************************************************************************/
int GetRelXSubTrack2(
	struct WTracks *wtrack,
	int subtrack
){
	return
		(wtrack->fxwidth*(subtrack+1)/wtrack->num_vel) - 
		(subtrack == wtrack->num_vel-1 ? 0 : 1)
	;
}

/************************************************************************
  FUNCTION
    Returns the absolute right X coordinate to track->fx.y for the subtrack
    'subtrack'.
************************************************************************/
int GetXSubTrack2(
	struct WTracks *wtrack,
	int subtrack
){
	if(subtrack==-1) return wtrack->notearea.x2;
	return wtrack->fxarea.x + GetRelXSubTrack2(wtrack,subtrack);
}

/************************************************************************
  FUNCTION
    These two functions works just like GetXSubTrack1 and 2, except
    that they allso accept the tracks that contains to the block. Which
    is the lpb-track, tempo-track, and the temponode-track.
************************************************************************/
int GetXSubTrack_B1(
	struct WBlocks *wblock,
	NInt track,
	int subtrack
){
	if(track>=0) return GetXSubTrack1(ListFindElement1(&wblock->wtracks->l,track),subtrack);
	switch(track){
		case LPBTRACK:
			return wblock->lpbarea.x;
			break;
		case TEMPOTRACK:
			return wblock->tempoarea.x;
			break;
		case TEMPONODETRACK:
			return wblock->temponodearea.x;
			break;
	};
	RError("Error in function GetXSubTrack_B1 in file gfx_subtrack.c\n");
	return 0;
}

int GetXSubTrack_B2(
	struct WBlocks *wblock,
	NInt track,
	int subtrack
){
	if(track>=0) return GetXSubTrack2(ListFindElement1(&wblock->wtracks->l,track),subtrack);
	switch(track){
		case LPBTRACK:
			return wblock->lpbarea.x2;
			break;
		case TEMPOTRACK:
			return wblock->tempoarea.x2;
			break;
		case TEMPONODETRACK:
			return wblock->temponodearea.x2;
			break;
	};
	RError("Error in function GetXSubTrack_B2 in file gfx_subtrack.c\n");
	return 0;
}

/************************************************************************
  FUNCTION
    Make shure that x is placed within the boundaries of the subtrack.
************************************************************************/
int SubtrackBoundaries(struct WTracks *wtrack,int subtrack,int x){
	int x1=GetRelXSubTrack1(wtrack,subtrack);
	int x2=GetRelXSubTrack2(wtrack,subtrack);
	if(x<x1) return x1;
	if(x>x2) return x2;
	if(x==2000) printf("2000\n");
	return x;
}


int GetSubTrackWidth(struct WTracks *wtrack,int subtrack){
	return GetXSubTrack2(wtrack,subtrack)-GetXSubTrack1(wtrack,subtrack);
}


/**************************************************************
  FUNCTION
    Returns the relative X position according to X1 value
    of the wtrack 'wtrack', calculated from the vector (x,maxx).
  INPUTS
    subtrack - Start at zero.
**************************************************************/
int GetSubTrackPos(
	struct WTracks *wtrack,
	float x,
	int maxx,
	int subtrack
){
	float x2;

	x2=x*GetSubTrackWidth(wtrack,subtrack)/maxx;
	x2=x2+GetRelXSubTrack1(wtrack,subtrack);

	return (int) (x2+0.5);
}

/**************************************************************
  FUNCTION
    Returns the subtrack 'x' belongs to in the wtrack 'wtrack'.
    If it doesn't belong to a subtrack. Returns -2;
**************************************************************/
int GetSubTrack(
	struct WTracks *wtrack,
	int x
){
	int lokke;
	int num_vel=wtrack->num_vel;

	for(lokke= -1;lokke<num_vel;lokke++){
		if(x==SubtrackBoundaries(wtrack,lokke,x)) return lokke;
	}

	return -2;
}




