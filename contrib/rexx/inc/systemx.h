/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1998/07/02 17:35:50  bnv
 * Initial revision
 *
 *
 * Function prototypes for calling external programs
 */

/* ---------------------------------------------------------- */
/* like system() function except that it returns the real     */
/* Return Code from the function                              */
/* ---------------------------------------------------------- */
extern int far systemx(const char far *cmd);

/* ----------------------------------------------BNV 1991 --- */
/* prototype to call asm int2e back door of command.com       */
/* int2e, executes a dos command without loading command.com  */
/* but uses the parent proccess command interpreter           */
/* ---------------------------------------------------------- */
extern void far int2e(char far *);
