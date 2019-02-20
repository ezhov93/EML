/*
 * @file   character.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Character utility functions.
 */

#ifndef ECHAR_H
#define ECHAR_H

#ifdef __cplusplus
extern "C" {
#endif

bool isAlphaNumeric(int c);
bool isAlpha(int c) __attribute__((always_inline));
bool isAscii(int c) __attribute__((always_inline));
bool isWhitespace(int c) __attribute__((always_inline));
bool isControl(int c) __attribute__((always_inline));
bool isDigit(int c) __attribute__((always_inline));
bool isGraph(int c) __attribute__((always_inline));
bool isLowerCase(int c) __attribute__((always_inline));
bool isPrintable(int c) __attribute__((always_inline));
bool isPunct(int c) __attribute__((always_inline));
bool isSpace(int c) __attribute__((always_inline));
bool isUpperCase(int c) __attribute__((always_inline));
bool isHexadecimalDigit(int c) __attribute__((always_inline));
int toAscii(int c) __attribute__((always_inline));
int toLowerCase(int c) __attribute__((always_inline));
int toUpperCase(int c)__attribute__((always_inline));

#ifdef __cplusplus
}
#endif

#endif // ECHAR_H
