/*
 * @file  enew.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  New type definitions
 */

#include <stdlib.h>

#if (__ARMCOMPILER_VERSION < 6000000)
void *operator new(size_t size) { return malloc(size); }

void *operator new[](size_t size) { return malloc(size); }

void operator delete(void *ptr) { free(ptr); }

void operator delete[](void *ptr) { free(ptr); }
#endif
