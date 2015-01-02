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
#include "gfx_wtext_proc.h"
#include "list_proc.h"
#include "common_proc.h"
#include "gfx_subtrack_proc.h"
#include "cursor_proc.h"
#include "placement_proc.h"
#include "clipboard_range_calc_proc.h"
#include "wblocks_proc.h"
#include "blts_proc.h"

#include "gfx_wtracks_proc.h"



extern struct Root *root;
extern char *NotesTexts3[131];
extern char *NotesTexts2[131];

/*
int OnC[4]={0,1,2,3};
int OffC[4]={3,2,1,0};
int *Col=OffC;

0,1,2 : 1
3   : 2
4   : 3
5   : 4
6   : 5
7   : 6
8,9,A : 7
*/
static const int Col[4]={0,1,2,3};
static const int NCol[11]={1,1,1,2,3,4,5,6,7,7,7};


void DrawWTrackBorder(struct Tracker_Windows *window,struct WBlocks *wblock,struct WTracks *wtrack){

	if(wtrack->x2>wblock->temponodearea.x2 && wtrack->x2+2<wblock->a.x2)
		GFX_V_DrawTrackBorderDouble(
			window,
			wtrack->x2+1,
			wtrack->y,
			wblock->a.y2
		);

	if(wtrack->notearea.x2>wblock->temponodearea.x2 && wtrack->notearea.x2+1<wblock->a.x2)
		GFX_V_DrawTrackBorderSingle(
			window,
			wtrack->notearea.x2+1,
			wblock->t.y1,
			wblock->a.y2
		);
	/*
	GFX_T_Line(
		window,Col[1],
		wtrack->x,
		wblock->t.y1-1,
		min(wtrack->x2-1,wblock->a.x2),
		wblock->t.y1-1
	);
	*/
}


void DrawAllWTracksBorders(struct Tracker_Windows *window,struct WBlocks *wblock){
	struct WTracks *wtrack=ListFindElement1(&wblock->wtracks->l,wblock->left_track);

	while(wtrack!=NULL && wtrack->l.num<=wblock->right_track){
		if(wtrack->notearea.x2+1<wblock->a.x2){
			DrawWTrackBorder(window,wblock,wtrack);
		}
		wtrack=NextWTrack(wtrack);
	}
}

void ClearTrack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int start_realline,
	int end_realline
){
  int lokke;

	if(WBlock_legalizeStartEndReallines(wblock,&start_realline,&end_realline)==false){
	  return;
	}

	for(lokke=start_realline;lokke<=end_realline;lokke++){
	  GFX_P_T_FilledBox(
			  window,Col[0],
			  max(wtrack->notearea.x,wblock->temponodearea.x2+2),
			  GetReallineY1Pos(window,wblock,lokke),
			  min(wtrack->fxarea.x2,wblock->a.x2),
			  GetReallineY2Pos(window,wblock,lokke)
			  );
	}
	//	SetCursorPos(window);
}

void ClearAllTrack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int start_realline,
	int end_realline,
	int start_subtrack,
	int end_subtrack
){
//	int lokke;

	printf("ca1. note.x: %d, note.x2-1: %d\n",wtrack->notearea.x,wtrack->notearea.x2-1);
	printf("%d - %d\n",start_realline,end_realline);

/*
	if(start_subtrack==-1)
		GFX_P_FilledBox(
			window,Col[0],
			wtrack->notearea.x,
			GetReallineY1Pos(window,wblock,start_realline),
			wtrack->notearea.x2-1,
			GetReallineY2Pos(window,wblock,end_realline)
		);

	printf("ca2\n");
	GFX_P_FilledBox(
		window,Col[0],
		max(wtrack->fxarea.x,wblock->temponodearea.x2+2),
		wblock->t.y1,
		min(wtrack->fxarea.x2,wblock->a.x2),
		wblock->t.y2
	);

	printf("ca3\n");
	for(lokke=start_subtrack>0 ? start_subtrack : 1;lokke<=end_subtrack;lokke++){
	printf("ca4\n");
		GFX_V_DrawTrackBorderSingle(
			 window,
			 GetXSubTrack1(wtrack,lokke)-1,
			 wblock->t.y1,
			 wblock->t.y2
		);
	}

	printf("ca5\n");
	if(wtrack->track->onoff==0){
	printf("ca6\n");
		GFX_P_FilledBox(window,Col[2],
			wtrack->x+window->fontwidth,wblock->t.y1+window->fontheight,
			wtrack->x2-window->fontwidth,wtrack->y2-window->fontheight
		);
	}
	printf("ca7\n");
*/
	//	SetCursorPos(window);
}



void WTRACK_DrawTrackBorders(
			       struct Tracker_Windows *window,
			       struct WBlocks *wblock,
			       struct WTracks *wtrack,
			       int realline,
			       int start_subtrack,
			       int end_subtrack
){
  int lokke;
  int y1=GetReallineY1Pos(window,wblock,realline);
  int y2=GetReallineY2Pos(window,wblock,realline);

  //  printf("start: %d, end: %d\n",start_subtrack,end_subtrack);

  if(wtrack->x2>wblock->temponodearea.x2+3 && wtrack->x2+2<wblock->a.x2)
    GFX_P_T_DrawTrackBorderDouble(
				window,
				wtrack->x2+1,
				y1,
				y2
				);

  if(wtrack->notearea.x2>wblock->temponodearea.x2 && wtrack->notearea.x2+1<wblock->a.x2)
    GFX_P_T_DrawTrackBorderSingle(
				window,
				wtrack->notearea.x2+1,
				y1,
				y2
				);

  for(lokke=start_subtrack>0 ? start_subtrack : 1;lokke<=end_subtrack;lokke++){
    GFX_P_T_DrawTrackBorderSingle(
				window,
				GetXSubTrack1(wtrack,lokke)-1,
				y1,
				y2
				);
  }
}

/*******************************************************
   TODO
     This function started out to be very nice and easy
     to read. After a while, when I added more new
     functions, it became uglier and uglier. It should
     be split up or something. There will probably be
     problems here later because of its complexity.
*******************************************************/

void UpdateWTrack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack,
	int start_realline,
	int end_realline
){
	int lokke;
	int start_subtrack= -1;
	int end_subtrack;

	char **NotesTexts;

	bool isranged=wblock->isranged ? wblock->rangex1<=wtrack->l.num ? wblock->rangex2>=wtrack->l.num ? true : false : false : false; // The ugliest code-line in the program? :)
	struct ListHeader3 *l;
	bool ranged=false,notranged=false;

	WFXNodes *wfxnode;
	struct TrackRealline *trackrealline;
	struct TrackReallineElements *element;

	if(WBlock_legalizeStartEndReallines(wblock,&start_realline,&end_realline)==false){
	  return;
	}

	NotesTexts=wtrack->notelength==3?NotesTexts3:NotesTexts2;

	if(wtrack->l.num==wblock->left_track){
		start_subtrack=wblock->left_subtrack;
	}

	if(wtrack->l.num==wblock->right_track){
	  end_subtrack=wblock->right_subtrack;
	  // end_subtrack=wtrack->num_vel-1;
	}else{
		end_subtrack=wtrack->num_vel-1;
	}

//	printf("1\n");
	if(wtrack->l_num_vel!=wtrack->num_vel || root->clearall==1){
//		ClearAllTrack(window,wblock,wtrack,start_realline,end_realline,start_subtrack,end_subtrack);
		wtrack->l_num_vel=wtrack->num_vel;
	}

//	printf("2\n");

	for(lokke=start_realline;lokke<=end_realline;lokke++){


		trackrealline= &wtrack->trackreallines[lokke];
		//		if(start_subtrack==-1){
		if(1){

			if(
				isranged
			){
				if(trackrealline->note!=0){
					if(trackrealline->note==NOTE_MUL){
						element=trackrealline->trackreallineelements;
						while(element!=NULL){
							if(element->type==TRE_THISNOTELINES || element->type==TRE_STOPLINE){
								l=(struct ListHeader3 *)element->pointer;
								if( isPlaceRanged(wblock,&l->p) ){
									ranged=true;
								}else{
									notranged=true;
								}
								if(ranged && notranged) break;
							}
							element=element->next;
						}
						if(ranged && notranged){
							SetInvertTextLine(
								window,
								wblock,
								Col[1],
								NotesTexts[NOTE_MUR],	//Is this possible? Will it ever happen?
								wtrack->notearea.x,
								lokke,
								true
							);
						}else{
							if(ranged){
								SetInvertTextLine(
									window,
									wblock,
									Col[1],
									NotesTexts[trackrealline->note],
									wtrack->notearea.x,
									lokke,
									true
								);
							}else{
								SetTextLine(
									window,
									wblock,
									Col[1],
									NotesTexts[trackrealline->note],
									wtrack->notearea.x,
									lokke,
									true
								);
							}
						}
					}else{
						element=trackrealline->trackreallineelements;
						while(element->type!=TRE_THISNOTELINES && element->type!=TRE_STOPLINE){
							element=element->next;
						}
						l=(struct ListHeader3 *)element->pointer;
						if( isPlaceRanged(wblock,&l->p) ){
							SetInvertTextLine(
								window,
								wblock,
								Col[1],
								NotesTexts[trackrealline->note],
								wtrack->notearea.x,
								lokke,
								true
							);
						}else{
							SetTextLine(
								window,
								wblock,
//								Col[1],
								trackrealline->note==NOTE_STP||trackrealline->note==NOTE_MUL?1:
									NCol[trackrealline->note/12],
								NotesTexts[trackrealline->note],
								wtrack->notearea.x,
								lokke,
								true
							);
						}
					}
				}else{
					if(lokke>=wblock->rangey1 && lokke<wblock->rangey2){
						SetInvertTextLineNotext(
									window,wblock,Col[1],
									wtrack->notelength,
									wtrack->notearea.x,lokke,
									true
									);
					}
				}
			}else{
				if(trackrealline->note!=0){
					SetTextLine(
						window,
						wblock,
						trackrealline->note==NOTE_STP||trackrealline->note==NOTE_MUL?1:
							NCol[trackrealline->note/12],
						NotesTexts[trackrealline->note],
						wtrack->notearea.x,
						lokke,
						true
					);
				}
			}
		}

		for(element=trackrealline->trackreallineelements;element!=NULL;element=element->next){
		  //		  if(element->subtype>end_subtrack || element->subtype<start_subtrack) continue;
			switch(element->type){
				case TRE_THISNOTELINES:
				  //					if(start_subtrack<=0)
				  
						GFX_P_T_Line(
							window,Col[3],
							wtrack->fxarea.x+element->x1,
							GetReallineY1Pos(window,wblock,lokke)+element->y1,
							min(wblock->t.x2,wtrack->fxarea.x+element->x2),
							GetReallineY1Pos(window,wblock,lokke)+element->y2
						);
				  
					break;
				case TRE_VELLINEEND:
				case TRE_VELLINESTART:
/*
					GFX_P_T_FilledBox(
						window,Col[3],
						wtrack->fxarea.x+element->x1,
						GetReallineY1Pos(window,wblock,lokke)+element->y1,
						wtrack->fxarea.x+element->x2,
						GetReallineY1Pos(window,wblock,lokke)+element->y2
					);
					break;
*/
				case TRE_VELLINENODE:
					GFX_P_T_Box(
						window,Col[3],
						wtrack->fxarea.x+element->x1,
						GetReallineY1Pos(window,wblock,lokke)+element->y1,
						wtrack->fxarea.x+element->x2,
						GetReallineY1Pos(window,wblock,lokke)+element->y2
					);
					GFX_P_T_FilledBox(
						window,Col[2],
						wtrack->fxarea.x+element->x1+1,
						GetReallineY1Pos(window,wblock,lokke)+element->y1+1,
						wtrack->fxarea.x+element->x2-1,
						GetReallineY1Pos(window,wblock,lokke)+element->y2-1
					);
					break;
				case TRE_VELLINE:
				case TRE_STOPLINE:
					GFX_P_T_Line(
						window,Col[1],
						wtrack->fxarea.x+element->x1,
						GetReallineY1Pos(window,wblock,lokke)+element->y1,
						wtrack->fxarea.x+element->x2,
						GetReallineY1Pos(window,wblock,lokke)+element->y2
					);
					break;
			case TRE_REALSTARTSTOP:
					GFX_P_T_Line(
						window,Col[2],
						wtrack->fxarea.x+element->x1,
						GetReallineY1Pos(window,wblock,lokke)+element->y1,
						wtrack->fxarea.x+element->x2,
						GetReallineY1Pos(window,wblock,lokke)+element->y2
					);
					break;
			}
		}

		WTRACK_DrawTrackBorders(window,wblock,wtrack,lokke,start_subtrack,end_subtrack);

		wfxnode=wtrack->wfxnodes[lokke];
		while(wfxnode!=NULL){
			switch(wfxnode->type){
				case TRE_FXLINE:
					GFX_P_T_Line(
						window,wfxnode->subtype, //Col[2],
						wtrack->fxarea.x+wfxnode->x1,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y1,
						wtrack->fxarea.x+wfxnode->x2,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y2
					);
					break;
				case TRE_FXNODE:
/*
					GFX_P_T_FilledBox(
						window,0,//wfxnode->subtype, //Col[3],
						wtrack->fxarea.x+wfxnode->x1+1,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y1+1,
						wtrack->fxarea.x+wfxnode->x2-1,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y2-1
					);
*/
					GFX_P_T_Box(
//						window,wfxnode->subtype==1?2:wfxnode->subtype>=4?wfxnode->subtype%3+1==1?2:Col[1]:Col[1],
						window,wfxnode->subtype,
//						window,1,
						wtrack->fxarea.x+wfxnode->x1,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y1,
						wtrack->fxarea.x+wfxnode->x2,
						GetReallineY1Pos(window,wblock,lokke)+wfxnode->y2
					);
					break;
			}
			wfxnode=wfxnode->next;
		}
	}

	Blt_markSTrack(window,wtrack->l.num,start_realline,end_realline);
}


void DrawUpWTrack(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	struct WTracks *wtrack
	){
  ClearTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
  UpdateWTrack(window,wblock,wtrack,wblock->top_realline,wblock->bot_realline);
}

void DrawUpAllWTracks(
	struct Tracker_Windows *window,
	struct WBlocks *wblock
){
	struct WTracks *wtrack=ListFindElement1(&wblock->wtracks->l,wblock->left_track);

	while(wtrack!=NULL && wtrack->l.num<=wblock->right_track){
	  DrawUpWTrack(window,wblock,wtrack);
	  wtrack=NextWTrack(wtrack);
	}
}

/*******************************************************
   Draw Up all visible tracks.
*******************************************************/
void UpdateAllWTracks(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	int start_realline,
	int end_realline
){
	struct WTracks *wtrack=ListFindElement1(&wblock->wtracks->l,wblock->left_track);

	while(wtrack!=NULL && wtrack->l.num<=wblock->right_track){
		UpdateWTrack(window,wblock,wtrack,start_realline,end_realline);
		wtrack=NextWTrack(wtrack);
	}
}


void UpdateAndClearSomeWTracks(
	struct Tracker_Windows *window,
	struct WBlocks *wblock,
	NInt starttrack,
	NInt endtrack,
	int start_realline,
	int end_realline
){
	NInt lokke;

	struct WTracks *wtrack=ListFindElement1(&wblock->wtracks->l,starttrack);
	if(wtrack==NULL) return;

	endtrack=min(endtrack,wblock->right_track);

	for(lokke=0;lokke<=endtrack-starttrack;lokke++){
		ClearTrack(window,wblock,wtrack,start_realline,end_realline);
		UpdateWTrack(window,wblock,wtrack,start_realline,end_realline);
		wtrack=NextWTrack(wtrack);
		if(wtrack==NULL) break;
	}

}



