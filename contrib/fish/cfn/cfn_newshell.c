/* - cfn -  completes filenames when pressing the "TAB" key */

/*  written in 1993 by Andreas G�nther                      */

/*  ( compiled with aztec-C 5.2 )                           */
/*  for more information, please read the doc-file          */


/*  this is NOT great artwork, so                           */

/*           FEEL FREE TO IMPROVE THIS CODE !               */



/* note: this piece of code is real public domain, do with  */
/*       it whatever you want, but I would be happy if you  */
/*       left my name in it :)                              */


/*  this is just a little program that should be put        */
/*  into the "S:shell-startup"-script.                      */
/*  It puts the address of the process structure of the     */
/*  shell that have just been launched into the user-data   */
/*  field of the window structure (if there is one).        */



#include "exec/types.h"
#include "intuition/intuitionbase.h"
#include <proto/exec.h>
#include <proto/intuition.h>

//#include "functions.h"
#include <stdio.h>

char *ver="$VER: cfn 1.0 (21.6.93)  by Andreas G�nther";

struct IntuitionBase *IntuitionBase=NULL;
ULONG ilock;


int main(int argc, char **argv)
{
  if(NULL==(IntuitionBase = (struct IntuitionBase *) OpenLibrary("intuition.library",0)))
    printf("ERROR: could not open intuition.library !\n");
  else
   {
    ilock=LockIBase(0);
    if(IntuitionBase->ActiveWindow!=NULL)   /* oh, what a hack... :) */
      if(IntuitionBase->ActiveWindow->UserData==NULL)
        IntuitionBase->ActiveWindow->UserData=(APTR)FindTask(NULL);
    UnlockIBase(ilock);
    CloseLibrary((struct Library *)IntuitionBase);
   }
  return 0;
}
