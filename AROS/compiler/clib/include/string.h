#ifndef _STRING_H
#define _STRING_H

/*
    (C) 1995-96 AROS - The Amiga Replacement OS
    $Id$

    Desc: ANSI-C header file string.h
    Lang: english
*/
#ifndef _SYS_TYPES_H
#   include <sys/types.h>
#endif

size_t strlen (const char * str);
int strcasecmp (const char * s1, const char * s2);
int strcmp (const char * s1, const char * s2);
int strncmp (const char * s1, const char * s2, size_t n);
char * strdup (const char * str);
char * strcpy (char * dest, const char * src);
char * strcat (char * dest, const char * src);
size_t strcspn (const char *s1, const char *s2);
char * strerror (size_t n);
char * strncat (char * dest, const char * src, size_t n);
char * strncpy (char * dest, const char * src, size_t n);
char * strpbrk (const char * s1, const char * s2);
char * strchr (const char * s, int c);
char * strrchr (const char * s, int c);
size_t strspn (const char * s1, const char * s2);
char * strstr (const char * buf, const char * str);
char * strtok (char * s1, const char * s2);

void * memchr (const void * dest, int c, size_t n);
int memcmp (const void * s1, const void * s2, size_t n);
void * memcpy (void * dest, const void * src, size_t n);
void * memmove (void * dest, const void * src, size_t n);
void * memset (void * dest, int c, size_t n);
void bcopy (const void * src, void * dst, int n);
void bzero (void * src, int n);

/* Macros */
#define stricmp  strcasecmp
#define strnicmp strncasecmp

#endif /* _STRING_H */
