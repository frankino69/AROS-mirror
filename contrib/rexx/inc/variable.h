/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.2  1999/11/29 14:58:00  bnv
 * Changed: Some defines
 *
 * Revision 1.1  1998/07/02 17:35:50  bnv
 * Initial revision
 *
 */

#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <bintree.h>

/* ------------ some defines ------------------ */
#define VARTREES	7
#define NO_CACHE	-1
#define NO_PROC		-1

/* --- Read VarTree options --- */
#define RVT_NOTHING	0
#define RVT_DEPTH	1
#define RVT_HEX		2

#define LEAFVAL(leaf)	&(((Variable*)((leaf)->value))->value)

typedef BinTree *Scope;

typedef
struct tvariable {
	Lstr	value;
	Scope	stem;
	bool	exposed;
} Variable;

/* --------------- function prototypes ----------------- */
void	RxInitVariables(void);
void	RxDoneVariables(void);
void	RxVarFree(void *var);
PBinLeaf RxVarAdd(Scope scope, PLstr name, int hasdot, PBinLeaf stemleaf );
PBinLeaf RxVarFind(const Scope scope, const PBinLeaf litleaf, bool *found);
PBinLeaf RxVarFindOld(Scope scope, PLstr name, bool *found);
void	RxVarDel(Scope scope, PBinLeaf litleaf, PBinLeaf varleaf);
void	RxVarDelOld(Scope scope, PLstr name, PBinLeaf varleaf);
void	RxVarDelInd(Scope scope, PLstr vars);
PBinLeaf RxVarExpose(Scope scope, PBinLeaf litleaf);
void	RxVarSet(Scope scope, PBinLeaf varleaf, PLstr value);
void	RxSetSpecialVar(int,long);
Scope	RxScopeMalloc( void );
void	RxScopeFree(Scope scope);
void	RxScopeAssign(PBinLeaf leaf);

void	RxVar2Str( PLstr result, PBinLeaf leaf, int option );
void	RxReadVarTree(PLstr result, Scope scope, PLstr head, int option);

int	RxRegPool(char *poolname, int (*getf)(PLstr,PLstr),
                        int (*setf)(PLstr,PLstr));
	
#undef EXTERN
#endif
