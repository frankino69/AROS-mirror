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

#ifndef __NEXTSYMBOL_H__
#define __NEXTSYMBOL_H__

#include <lstring.h>

#ifdef __NEXTSYMB_C__
#	define EXTERN
#else
#	define EXTERN extern
#endif


enum symboltype {
	 ident_sy			/* identifier symbol	*/
	,function_sy			/* ident with a paren	*/
	,literal_sy			/* literal symbol	*/
	,le_parent			/*     (    */ /* the order    */
	,le_bracket			/*     [    */ /* until        */
	,le_curlbracket			/*     {    */ /* not_ty       */
	,plus_sy			/*     +    */ /* is important */
	,inc_sy				/*    ++    */ /* for expr.c   */
	,minus_sy			/*     -    */
	,dec_sy				/*    --    */
	,not_sy				/*  ^ or \  */ /* ------------ */

	,eq_sy       ,deq_sy		/*   =  ==  */ /* eq_sy - first	*/
	,ne_sy       ,dne_sy		/*  ^= ^==  */
	,le_sy       ,ge_sy		/*  <=  =>  */
	,lt_sy       ,gt_sy		/*   <  >   */
	,dle_sy      ,dge_sy            /* <<=  =>> */
	,dlt_sy      ,dgt_sy            /*  <<  >>  */

	,times_sy			/*     *    */ /* another group   */
	,div_sy				/*     /    */
	,mod_sy				/*     %    */
	,intdiv_sy			/*    //    */ /* --------------- */

	,ri_parent			/*     )    */
	,ri_bracket			/*     ]    */
	,ri_curlbracket			/*     }    */
	,dot_sy				/*     .    */
	,tidle_sy			/*     ~    */

	,power_sy			/*    **    */
	,and_sy				/*     &    */
	,or_sy				/*     |    */
	,xor_sy				/*    &&    */
	,concat_sy			/*    ||    */
	,bconcat_sy			/*   |b|    */
	,comma_sy			/*     ,    */
	,semicolon_sy			/*     ;    */
	,to_sy				/* in_do    */
	,by_sy				/* in_do    */
	,for_sy				/* in_do    */
	,until_sy			/* in_do    */
	,while_sy			/* in_do    */
	,then_sy			/* in_if_...*/
	,with_sy			/* in_parse */
	,label_sy
	,exit_sy

/*---------------------------------------------------
	,div_assign_sy			*    /=    *
	,times_assign_sy		*    *=    *
	,mod_assign_sy			*    %=    *
	,power_assign_sy		*   **=    *
	,intdiv_assign_sy		*   //=    *
	,and_assign_sy			*    &=    *
	,plus_assign_sy			*    +=    *
	,minus_assign_sy		*    -=    *
	,concat_assign_sy		*   ||=    *
	,or_assign_sy			*    |=    *
	,xor_assign_sy			*   &&=    *
----------------------------------------------------*/
};

enum  stat_type {
	 normal_st		/* normal statement	*/
	,in_do_st
	,in_do_init_st
	,in_if_init_st
	,in_if_st
	,in_parse_value_st
};

EXTERN enum	symboltype symbol;	/* contains the symbol		*/
EXTERN Lstr	symbolstr;		/* symbol identifier		*/
EXTERN bool	symbolisstr;		/* if litteral was inside quotes*/
EXTERN bool	symbolPrevBlank;	/* previous blank		*/
EXTERN int	symbolhasdot;		/* is symbol has a dot->stem	*/
EXTERN char	*symbolptr;		/* current symbol pointer	*/
EXTERN char	*symbolprevptr;		/* start of current symbol	*/
EXTERN int	symboline;		/* current line number		*/
EXTERN enum	stat_type  symbolstat;	/* statement type		*/

/* -------- function prototypes ----------- */
void	InitNextsymbol( PLstr str );
void	nextsymbol(void);

#undef EXTERN
#endif
