/*
    (C) 2000 AROS - The Amiga Research OS
    $Id$

    Desc: 
    Lang: English
*/

/*****************************************************************************

    NAME

        Else

    SYNOPSIS

    LOCATION

        Workbench:C

    FUNCTION

        Separate the 'true' and 'false' blocks of an If statement. The block
	following an Else command is executed if the condition in the previous
	If statement was false.
	
    INPUTS

    RESULT

    NOTES

    EXAMPLE

        If EXISTS Sys:Devs
	    Copy random.device Sys:Devs/
	Else
	    Echo "Cannot find Sys:Devs"
	EndIf

    BUGS

    SEE ALSO

        If, EndIf

    INTERNALS

    HISTORY

    12.01.2000  SDuvan   implemented

******************************************************************************/

#include <dos/dos.h>
#include <dos/dosextens.h>
#include <dos/rdargs.h>
#include <dos/stdio.h>
#include <proto/dos.h>
#include <dos_commanderrors.h>


int main(int argc, char **argv)
{
    struct CommandLineInterface *cli = Cli();

    if((cli != NULL) && (cli->cli_CurrentInput != cli->cli_StandardInput))
    {
	BOOL found = FALSE;
	int  level = 1;
	char buffer[256];
	
	SelectInput(cli->cli_CurrentInput);

	while(!found)
	{
	    LONG status;
	    int temp;

	    status = ReadItem(buffer, sizeof(buffer), NULL);

	    if(status == ITEM_ERROR || ITEM_NOTHING)
		break;

	    switch((temp = FindArg("IF,ENDIF", buffer)))
	    {
	    case 0:
		level++;
		break;
		
	    case 1:
		level--;

		if(level == 0)
		    found = TRUE;
		break;
	    }

	    /* Take care of long lines */
	    {
		char a;
		do {
		    a = FGetC(Input());
		} while(a != '\n' && a != ENDSTREAMCH);
	    }
	}

	if(!found)
	{
	    PrintFault(ERROR_NO_MATCHING_ELSEENDIF, "Else");
	    return RETURN_FAIL;
	}
    }
    else
    {
	PrintFault(ERROR_SCRIPT_ONLY, "Else");
	return RETURN_ERROR;
    }

    return RETURN_OK;
}
