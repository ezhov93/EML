/*
 * @file  enew.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  New type definitions
 */

#include <stdlib.h>

void new(void *data, size_t size) {
  data = (void *) malloc(size);
}


void delete(void *ptr) {
  free(ptr);
}

