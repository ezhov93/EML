/*
 * @file   character.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Character utility functions.
 */

#include "echar.h"
#include <ctype.h>
#include "etypes.h"

inline bool isAlphaNumeric(int c) {
  return ( isalnum(c) == 0 ? false : true);
}

inline bool isAlpha(int c)  {
  return ( isalpha(c) == 0 ? false : true);
}

inline bool isAscii(int c)  {
/*  return ( isascii(c) == 0 ? false : true); */
  return ( (c & ~0x7f) != 0 ? false : true);
}

inline bool isWhitespace(int c) {
  return ( isblank (c) == 0 ? false : true);
}

inline bool isControl(int c)  {
  return ( iscntrl (c) == 0 ? false : true);
}

inline bool isDigit(int c)  {
  return ( isdigit (c) == 0 ? false : true);
}

inline bool isGraph(int c)  {
  return ( isgraph (c) == 0 ? false : true);
}

inline bool isLowerCase(int c)  {
  return (islower (c) == 0 ? false : true);
}

inline bool isPrintable(int c)  {
  return ( isprint (c) == 0 ? false : true);
}

inline bool isPunct(int c)  {
  return ( ispunct (c) == 0 ? false : true);
}

inline bool isSpace(int c)  {
  return ( isspace (c) == 0 ? false : true);
}

// Checks for an uppercase letter.
inline bool isUpperCase(int c)  {
  return ( isupper (c) == 0 ? false : true);
}

inline bool isHexadecimalDigit(int c) {
  return ( isxdigit (c) == 0 ? false : true);
}

inline int toAscii(int c) {
/*  return toascii (c); */
  return (c & 0x7f);
}

inline int toLowerCase(int c) {
  return tolower (c);
}

inline int toUpperCase(int c) {
  return toupper (c);
}

