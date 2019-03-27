/*
 * @file  new.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  New type definitions
 */

#include <stdlib.h>

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void * ptr);
void operator delete[](void * ptr);

