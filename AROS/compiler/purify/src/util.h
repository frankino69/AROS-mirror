#ifndef _UTIL_H
#define _UTIL_H

#define xmalloc _Purify_xmalloc
#define xfree	_Purify_xfree

void * xmalloc (int size);
void xfree (void *);

#endif /* _UTIL_H */
