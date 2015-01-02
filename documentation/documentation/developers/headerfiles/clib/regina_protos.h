#ifndef CLIB_REGINA_PROTOS_H
#define CLIB_REGINA_PROTOS_H

/*
    *** Automatically generated from 'regina.conf'. Edits will be lost. ***
    Copyright � 1995-2008, The AROS Development Team. All rights reserved.
*/

#include <aros/libcall.h>

#include <rexx/storage.h>
#ifndef INCL_REXXSAA
#define INCL_REXXSAA
#endif
#include <rexxsaa.h>

ULONG RexxStart(LONG ArgCount, PRXSTRING ArgList, PCSZ ProgName, PRXSTRING Instore, PCSZ EnvName, LONG CallType, PRXSYSEXIT Exits, PSHORT ReturnCode, PRXSTRING Result);
ULONG RexxRegisterSubcomExe(PCSZ EnvName, PFN EntryPoint, PUCHAR UserArea);
ULONG RexxRegisterSubcomDll(PCSZ EnvName, PCSZ ModuleName, PCSZ ProcedureName, PUCHAR UserArea, ULONG DropAuth);
ULONG RexxQuerySubcom(PCSZ EnvName, PCSZ ModuleName, PUSHORT Flag, PUCHAR UserWord);
ULONG RexxDeregisterSubcom(PCSZ EnvName, PCSZ ModuleName);
ULONG RexxVariablePool(PSHVBLOCK RequestBlockList);
ULONG RexxRegisterExitExe(PCSZ EnvName, PFN EntryPoint, PUCHAR UserArea);
ULONG RexxRegisterExitDll(PCSZ EnvName, PCSZ ModuleName, PCSZ ProcedureName, PUCHAR UserArea, ULONG DropAuth);
ULONG RexxDeregisterExit(PCSZ EnvName, PCSZ ModuleName);
ULONG RexxQueryExit(PCSZ EnvName, PCSZ ModuleName, PUSHORT Flag, PUCHAR UserArea);
ULONG RexxRegisterFunctionExe(PCSZ Name, PFN EntryPoint);
ULONG RexxRegisterFunctionDll(PCSZ ExternalName, PCSZ LibraryName, PCSZ InternalName);
ULONG RexxQueryFunction(PCSZ Name);
ULONG RexxDeregisterFunction(PCSZ Name);
ULONG RexxSetHalt(LONG dummyProcess, LONG dummyThread);
ULONG RexxCreateQueue(PSZ Buffer, ULONG BuffLen, PSZ RequestedName, ULONG *DupFlag);
ULONG RexxDeleteQueue(PSZ QueueName);
ULONG RexxQueryQueue(PSZ QueueName, ULONG *Count);
ULONG RexxAddQueue(PSZ QueueName, PRXSTRING EntryData, ULONG AddFlag);
ULONG RexxPullQueue(PSZ QueueName, PRXSTRING DataBuf, PDATETIME TimeStamp, ULONG WaitFlag);
ULONG RexxAddMacro(PSZ FuncName, PSZ SourceFile, ULONG Position);
ULONG RexxClearMacroSpace();
ULONG RexxDropMacro(PSZ FuncName);
ULONG RexxLoadMacroSpace(ULONG FuncCount, PSZ *FuncNames, PSZ MacroLibFile);
ULONG RexxQueryMacro(PSZ FuncName, PUSHORT Position);
ULONG RexxReorderMacro(PSZ FuncName, ULONG Position);
ULONG RexxSaveMacroSpace(ULONG FuncCount, PSZ *FuncNames, PSZ MacroLibFile);
ULONG RexxFreeMemory(PVOID MemoryBlock);
PVOID RexxAllocateMemory(ULONG Size);
ULONG ReginaVersion(PRXSTRING VersionString);
int __regina_faked_main(int argc, char *argv[]);
BOOL IsReginaMsg(struct RexxMsg *msg);

#endif /* CLIB_REGINA_PROTOS_H */
