/*
 * @file   eprintable.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Interface class that allows printing of complex types
 */

#ifndef EPRINTABLE_H
#define EPRINTABLE_H

#include <stdlib.h>

class EPrint;

/** The Printable class provides a way for new classes to allow themselves to be
   printed. By deriving from Printable and implementing the printTo method, it
   will then be possible for users to print out instances of this class by
   passing them into the usual Print::print and Print::println methods.
*/

class EPrintable {
 public:
  virtual size_t printTo(EPrint& p) const = 0;
};

#endif  // EPRINTABLE_H
