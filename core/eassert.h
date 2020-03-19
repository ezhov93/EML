/*
 * @file   ecore.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Assert include file.
 */

#ifndef EASSERT_H
#define EASSERT_H

#include "estream.h"

#ifdef EASSERT_FULL
#define eassert(expr)                                                         \
  ((expr) ? (void)0                                                           \
          : eassert_failed((char *)__func__, (char *)__FILE__, (int)__LINE__, \
                           #expr))
#else
#define eassert(expr) ((void)0)
#endif

void eassert_set(EStream *);
void eassert_failed(const char *func, const char *file, const int line,
                    const char *expr);

#endif  // EASSERT_H
