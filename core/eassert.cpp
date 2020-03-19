/*
 * @file   eassert.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Assert include source file.
 */

#include "eassert.h"
#include "estream.h"

EStream *stream = null;

void eassert_set(EStream *s) { stream = s; }

void eassert_failed(const char *func, const char *file, const int line,
                    const char *expr) {
  if (stream) {
    static const char *assertion = " Assertion `";
    static const char *failed = "\' failed";
    stream->println();
    stream->print("err: ");
    stream->flush();
    stream->print(file);
    stream->flush();
    stream->print(':');
    stream->flush();
    stream->print((int)line, 10);
    stream->flush();
    stream->print(':');
    stream->flush();
    stream->print(' ');
    stream->flush();
    stream->print(func);
    stream->flush();
    stream->print(':');
    stream->flush();
    stream->print(assertion);
    stream->flush();
    stream->print(expr);
    stream->flush();
    stream->print(failed);
    stream->flush();
  }
  while (1) {
  }
}
