#ifndef MCCCLASS_INTERFACE_DEF_H
#define MCCCLASS_INTERFACE_DEF_H

/*
** This file was machine generated by idltool 50.10.
** Do not edit
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif


struct MCCClassIFace
{
	struct InterfaceData Data;

	ULONG APICALL (*Obtain)(struct MCCClassIFace *Self);
	ULONG APICALL (*Release)(struct MCCClassIFace *Self);
	void APICALL (*Expunge)(struct MCCClassIFace *Self);
	struct Interface * APICALL (*Clone)(struct MCCClassIFace *Self);
	ULONG APICALL (*MCC_Query)(struct MCCClassIFace *Self, LONG which);
};

#endif /* MCCCLASS_INTERFACE_DEF_H */