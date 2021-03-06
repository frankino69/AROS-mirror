/*
    Copyright � 1995-2015, The AROS Development Team. All rights reserved.
    $Id$

    Desc:
    Lang: english
*/

/******************************************************************************


    NAME

        TaskList

    SYNOPSIS

        (N/A)

    LOCATION

        C:

    FUNCTION

        Prints a list of all tasks.

    INPUTS

    RESULT

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

    HISTORY

******************************************************************************/

#include <exec/memory.h>
#include <exec/tasks.h>
#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/timer.h>
#include <aros/debug.h>
#include <devices/timer.h>
#include <dos/dosextens.h>
#include <proto/dos.h>
#include <proto/task.h>

#include <resources/task.h>

const TEXT version[] = "$VER: tasklist 42.0 (02.5.2015)\n";

APTR TaskResBase = NULL;
ULONG eclock;

struct task
{
    STRPTR name;
    APTR address;
    WORD type;
    WORD state;
    IPTR stacksize;
    IPTR stackused;
    WORD pri;
    struct timeval cputime;
};

static int addtask(struct Task *task, struct task **t, STRPTR *e)
{
    STRPTR s1,s2;
    struct TagItem QueryTaskTags[] =
    {
        {TaskTag_CPUTime        , (IPTR)&(*t)->cputime  },
        {TAG_DONE               , 0                     }
    };

    QueryTaskTagList(task, QueryTaskTags);

    (*t)->address = task;
    (*t)->type = task->tc_Node.ln_Type;
    (*t)->pri = (WORD)task->tc_Node.ln_Pri;
    (*t)->state = task->tc_State;
    (*t)->stacksize = (STRPTR)task->tc_SPUpper - (STRPTR)task->tc_SPLower;
#if AROS_STACK_GROWS_DOWNWARDS
    (*t)->stackused = (STRPTR)task->tc_SPUpper - SP_OFFSET - (STRPTR)task->tc_SPReg;
#else
    (*t)->stackused = (STRPTR)task->tc_SPReg - SP_OFFSET - (STRPTR)task->tc_SPLower;
#endif
    if (task->tc_State == TS_RUN)
    {
        /* The tc_SPReg for the actual process is invalid
           if it had no context switch yet */
        (*t)->stackused = 0;
    }
    s1 = task->tc_Node.ln_Name;
    if (task->tc_Node.ln_Type == NT_PROCESS && ((struct Process *)task)->pr_CLI)
    {
	/* TODO: Use cli_CommandName field for the name */
        (*t)->type = -1;
    }
    if (s1 != NULL)
    {
        s2 = s1;

        while (*s2++)
            ;

        while (s2 > s1)
        {
            if (*e<=(STRPTR)*t)
                return 0;
            *--(*e)=*--s2;
        }
    }
    if ((STRPTR)(*t + 1) > *e)
        return 0;

    (*t)->name = *e;
    ++*t;

    return 1;
}

static int fillbuffer(struct task **buffer, IPTR size)
{
    STRPTR end = (STRPTR)*buffer + size;
    struct Task *task;

#if !defined(__AROS__)
    Disable();

    if (!addtask(FindTask(NULL), buffer, &end))
    {
        Enable();
        return 0;
    }
    for (task = (struct Task *)SysBase->TaskReady.lh_Head;
        task->tc_Node.ln_Succ != NULL;
        task = (struct Task *)task->tc_Node.ln_Succ)
    {
        if (!addtask(task, buffer, &end))
        {
            Enable();
            return 0;
        }
    }
    for (task = (struct Task *)SysBase->TaskWait.lh_Head;
        task->tc_Node.ln_Succ != NULL;
        task = (struct Task *)task->tc_Node.ln_Succ)
    {
        if (!addtask(task, buffer, &end))
        {
            Enable();
            return 0;
        }
    }
    Enable();
#else
    struct TaskList *taskList;

    taskList = LockTaskList(0);
    while ((task = NextTaskEntry(taskList, 0)) != NULL)
    {
        if (!addtask(task, buffer, &end))
        {
            break;
        }
    }
    UnLockTaskList(0);
#endif

    return 1;
}

int __nocommandline;

int main(void)
{
    IPTR size;
    struct task *buffer,*tasks,*tasks2;

    TaskResBase = OpenResource("task.resource");
    if (!TaskResBase) {
        FPuts(Output(),"Can't open task.resource\n");
        return 20;
    }

    for(size = 2048; ; size += 2048)
    {
        buffer = AllocVec(size, MEMF_ANY);
        if (buffer == NULL)
        {
            FPuts(Output(),"Not Enough memory for task buffer\n");
            return 20;
        }
        tasks = buffer;
        if (fillbuffer(&tasks, size))
        {
            FPuts(Output(), "Address\t\tType\tPri\tState\tCPU Time\tStack\tUsed\tName\n");
            for (tasks2 = buffer; tasks2 < tasks; tasks2++)
            {
            	ULONG time;

                IPTR args[10];
                args[0] = (IPTR)tasks2->address;
                args[1] = (IPTR)((tasks2->type == NT_TASK) ? "task" :
                	       (tasks2->type == NT_PROCESS) ? "process" : "CLI" );
                args[2] = tasks2->pri;
                args[3] = (IPTR)((tasks2->state == TS_RUN) ? "running" :
                	       (tasks2->state == TS_READY) ? "ready" : "waiting" );

                time = tasks2->cputime.tv_secs;
                args[6] = time % 60;
                time /= 60;
                args[5] = time % 60;
                time /= 60;
                args[4] = time % 60;

                args[7] = tasks2->stacksize;
                args[8] = tasks2->stackused;
                args[9] = (tasks2->name != NULL) ? (IPTR)tasks2->name : 0;
                VPrintf("0x%08.lx\t%s\t%ld\t%s\t%02ld:%02ld:%02ld\t%ld\t%ld\t%s\n", args);
            }
            FreeVec(buffer);
            return 0;
        }
        FreeVec(buffer);
    }
}
