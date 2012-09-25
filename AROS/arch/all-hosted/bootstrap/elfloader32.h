/*
 * Copyright (C) 2006 - 2011 The AROS Development Team. All rights reserved.
 * $Id$
 */


#ifndef ELFLOADER_H_
#define ELFLOADER_H_

typedef int (*kernel_entry_fun_t)(struct TagItem *, ULONG);

int AddKernelFile(char *name);
void FreeKernelList(void);
int GetKernelSize(size_t *ro_size, size_t *rw_size);
int LoadKernel(void *ptr_ro, void *ptr_rw, struct KernelBSS *tracker, kernel_entry_fun_t *kernel_entry, struct ELF_ModuleInfo **kernel_debug);

#endif /*ELFLOADER_H_*/