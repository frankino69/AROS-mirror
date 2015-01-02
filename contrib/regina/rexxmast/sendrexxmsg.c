#include <proto/alib.h>
#include <proto/exec.h>
#include <proto/rexxsyslib.h>
#include <stdio.h>
#include <string.h>

#include <exec/ports.h>
#include <rexx/storage.h>

int main(void)
{
   struct RexxMsg *msg, *reply;
   struct MsgPort *port, *replyport;
   const char *command = "'say hello everybody'";
    
   port = FindPort("REXX");
   if (port == NULL)
   {
      puts("REXX port not found");
      return 20;
   }

   replyport = CreatePort(NULL, 0);
   if (replyport == NULL)
   {
      puts("Could not create replyport");
      return 20;
   }
    
   msg = CreateRexxMsg(replyport, ".rexx", NULL);
   if (msg == NULL)
   {
      puts("Error creating RexxMsg");
      DeletePort(replyport);
      return 20;
   }
   msg->rm_Action = RXCOMM | RXFF_RESULT;
   msg->rm_Args[0] = (IPTR)CreateArgstring((STRPTR)command, strlen(command));
   PutMsg(port, (struct Message *)msg);
   reply = (struct RexxMsg *)WaitPort(replyport);
   printf("Result1: %ld\n", (long)reply->rm_Result1);
   if ((reply->rm_Result1==0) && (reply->rm_Result2!=0))
   {
      printf("Result2: %s\n", (STRPTR)reply->rm_Result2);
      DeleteArgstring((STRPTR)reply->rm_Result2);
   }
   DeleteArgstring((STRPTR)msg->rm_Args[0]);
   DeleteRexxMsg(msg);
   DeletePort(replyport);

   if (reply != msg)
   {
      puts("Returned message is different then sent message");
      return 20;
   }
    
   puts("All OK");
   return 0;
}
