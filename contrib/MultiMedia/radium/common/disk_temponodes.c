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
#include "disk.h"
#include "disk_placement_proc.h"
#include "placement_proc.h"

#include "disk_temponodes_proc.h"



void SaveTempoNodes(struct TempoNodes *temponode){
	struct TempoNodes *next=NextTempoNode(temponode);
	struct TempoNodes *last=(struct TempoNodes *)ListLastP(next);

DC_start("RELTEMPO");


	DC_SaveF(temponode->reltempo);
	DC_SaveF(last->reltempo);
	SavePlace(&last->l.p);

	if(next!=last){
		DC_start("TEMPONODES");
			do{
				SavePlace(&next->l.p);
				DC_SaveF(next->reltempo);
				next=NextTempoNode(next);
			}while(next!=last);
		DC_end();
	}

DC_end();
}


void LoadTempoNodes(struct TempoNodes **to){

	struct TempoNodes *temponode=DC_alloc(sizeof(struct TempoNodes));

	PlaceSetFirstPos(&temponode->l.p);
	temponode->reltempo=DC_LoadF();
	DC_ListAdd3(to,temponode);

	temponode=DC_alloc(sizeof(struct TempoNodes));
	temponode->reltempo=DC_LoadF();
	LoadPlace(&temponode->l.p);
	DC_ListAdd3(to,temponode);

	if(DC_Next()==LS_OBJECT){
		while(dc.success){
			DC_fgets();
			if(dc.ret[0]=='/'){
				DC_Next();
				break;
			}
			temponode=DC_alloc(sizeof(struct TempoNodes));
			temponode->Tline=atoi(dc.ret);
			temponode->Tcounter=DC_LoadU32();
			temponode->Tdividor=DC_LoadU32();
			temponode->reltempo=DC_LoadF();
			DC_ListAdd3(to,temponode);
		}
	}

error:
	return;
}



