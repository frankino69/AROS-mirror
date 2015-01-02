/*
    Copyright � 2003, The AROS Development Team. All rights reserved.
    $Id$
*/

#include "common.c"

/*** Main *******************************************************************/
int main()
{
    struct timeval  tv_start, 
                    tv_end;
    int             count   = 100000000;
    double          elapsed = 0.0;
    Object         *object  = NULL;
    int             i;
    
    if (!Test_Initialize()) goto error;
    
    object  = TestObject, End;
    
    gettimeofday(&tv_start, NULL);
    
    for(i = 0; i < count; i++)
    {    
        DoMethod(object, MUIM_Test_Dummy);        
    }
    
    gettimeofday(&tv_end, NULL);
    
    DisposeObject(object);
    
    elapsed = ((double)(((tv_end.tv_sec * 1000000) + tv_end.tv_usec) 
            - ((tv_start.tv_sec * 1000000) + tv_start.tv_usec)))/1000000.;
    
    printf
    (
        "Elapsed time:       %f seconds\n"
        "Number of calls:    %d\n"
        "Calls per second:   %f\n"
        "Seconds per call:   %f\n",
        elapsed, count, (double) count / elapsed, (double) elapsed / count
    );
    
    Test_Deinitialize();
    
    return 0;
    
error:
    printf("Could not initialize Test class!\n");

    return 20;
}
