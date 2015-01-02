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
#include "visual_proc.h"
#include <string.h>

#include "gfx_tempotrackheader_proc.h"

extern struct Root *root;

void UpdateTempoTrackHeader_reltempo(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	int color
){
	char temp[500];
	char *name="RelTempoMax (RelTempoMin is 1/RelTempoMax)";

	int numchars=(wblock->temponodearea.x2-wblock->temponodearea.x)/window->fontwidth;
	int presicion;

	char cuttemp=false;
	bool cut=false;

	if(numchars<=0) return;

	presicion=numchars-(wblock->reltempomax>=10.0 ? 3:2);

	if(presicion<0){
		temp[0]='*';
		temp[1]=0;
	}else{
		presicion=min(5,presicion);
		sprintf(
			temp,"%.*f",
			presicion,
			wblock->reltempomax
		);
		if(strlen(temp)>numchars){
			temp[0]='*';
			temp[1]=0;
		}
	}

	GFX_All_FilledBox(
		window,0,
		wblock->temponodearea.x+1,
		wblock->a.y1,
		wblock->temponodearea.x2,
		wblock->t.y1-2
	);

	GFX_Text(
		window,color,temp,
		wblock->temponodearea.x+1,
		wblock->a.y1+window->org_fontheight,false
	);

	sprintf(temp,"%.*s",numchars,name);
	if(numchars<strlen(name)-1){
		cuttemp=temp[numchars];
		temp[numchars]='\0';
		cut=true;
	}

	GFX_Text(
		window,1,temp,
		wblock->temponodearea.x+1,
		wblock->a.y1,false
	);

	if(cut){
		temp[numchars]=cuttemp;
	}
	GFX_Line(window,1,wblock->temponodearea.x+1,wblock->t.y1-1,wblock->temponodearea.x2+1,wblock->t.y1-1);
}

void UpdateTempoTrackHeader_LPB(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	int color
){
	char temp[50];

	GFX_Text(
		window,1,"LPB",
		wblock->lpbTypearea.x+1,
		wblock->a.y1,false
	);

	sprintf(temp,"%3d",root->lpb);
	GFX_Text(
		window,color,temp,
		wblock->lpbTypearea.x+1,
		wblock->a.y1+window->org_fontheight,false
	);
}


void UpdateTempoTrackHeader_BPM(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	int color
){
	char temp[50];

	GFX_Text(
		window,1,"BPM",
		wblock->tempoTypearea.x+1,
		wblock->a.y1,false
	);

	sprintf(temp,"%3d",root->tempo);
	GFX_Text(
		window,2,temp,
		wblock->tempoTypearea.x+1,
		wblock->a.y1+window->org_fontheight,false
	);
}


void UpdateTempoTrackHeader(
	struct Tracker_Windows *window,
	struct WBlocks *wblock
){
	UpdateTempoTrackHeader_LPB(window,wblock,2);
	UpdateTempoTrackHeader_BPM(window,wblock,2);
	UpdateTempoTrackHeader_reltempo(window,wblock,2);
}

void DrawTempoTrackHeader(
	struct Tracker_Windows *window,
	struct WBlocks *wblock
){
	GFX_FilledBox(
		window,0,
		wblock->lpbTypearea.x+1,
		wblock->a.y1,
		wblock->temponodearea.x2+3,
		wblock->t.y1-2
	);

	UpdateTempoTrackHeader_LPB(window,wblock,2);
	UpdateTempoTrackHeader_BPM(window,wblock,2);
	UpdateTempoTrackHeader_reltempo(window,wblock,2);
}

