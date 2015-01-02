/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:36  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:35:50  bnv
 * Initial revision
 *
 */

#ifndef __DEQUEUE_H__
#define __DEQUEUE_H__

#include <lstring.h>

/* ============= type definitions ================= */
typedef struct dequeue_elem_st {
	void	*dat;
	struct dequeue_elem_st	*prev, *next;
} DQueueElem;

typedef struct {
	long		items;
	DQueueElem	*head;
	DQueueElem	*tail;
} DQueue;

#define DQINIT(q)	{(q).items=0; (q).head=NULL; (q).tail=NULL;}
#define DQQUEUE(q,s)	DQAdd2Head(q,s)
#define DQPUSH(q,s)	DQAdd2Tail(q,s)
#define DQDELLAST(q)	DQDel(q,q->tail)
#define DQDELFIRST(q)	DQDel(q,q->head)
#define DQPEEK(q)	(((q)->tail)->dat)

/* ============= function prototypes ============= */
void	DQAdd2Head( DQueue *queue, void *dat);
void	DQAdd2Tail( DQueue *queue, void *dat);
void	*DQPop( DQueue *queue );
void	DQDel( DQueue *queue, DQueueElem *elem );
void	DQFlush( DQueue *queue, void (freefunc)(void *dat) );

/*DQueueElem *	DQFind( DQueue *queue, PLstr str );*/

#endif
