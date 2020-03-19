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
bool isAlpha(int c);
bool isAscii(int c);
bool isWhitespace(int c);
bool isControl(int c);
bool isDigit(int c);
bool isGraph(int c);
bool isLowerCase(int c);
bool isPrintable(int c);
bool isPunct(int c);
bool isSpace(int c);
bool isUpperCase(int c);
bool isHexadecimalDigit(int c);
int toAscii(int c);
int toLowerCase(int c);
int toUpperCase(int c);

#ifdef __cplusplus
}
#endif

#endif  // ECHAR_H
