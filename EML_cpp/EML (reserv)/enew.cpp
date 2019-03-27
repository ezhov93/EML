/*
 * @file  enew.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  New type definitions
 */

#include <stdlib.h>

void *operator new(size_t size) {
  return malloc(size);
}

void *operator new[](size_t size) {
  return malloc(size);
}

void operator delete(void * ptr) {
  free(ptr);
}

void operator delete[](void * ptr) {
  free(ptr);
}

