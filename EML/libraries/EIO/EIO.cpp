/*
 * @file   EIO.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Console input/output helper source file.
 */

#include "EIO.h"
#include "echar.h"

EString EIO::scan() {
  EString ret;
  int c = read();
  while (true)  {
    if (c>=0) {
      char ch = (char)c;
      if (ch == '\r' || ch == '\n')
        break;
      if (isPrintable(ch))
        ret += ch;
    }
    c = read();
  }
  println();
  return ret;
}

void EIO::scan(char* str) {
  char *ret;
  int c = read();
  while (true)  {
    if (c>=0) {
      char ch = (char)c;
      if (ch == '\r' || ch == '\n')
        break;
      if (isPrintable(ch))
        *ret++ = ch;
    }
    c = read();
  }
  println();
}

int EIO::read() {
  int ch = _parent->read();
  if (ch > 0 && isPrintable((char)ch)) write(ch);
  return ch;
}

size_t EIO::begin(Style style, Color color, Color background) {
  size_t n = EPrint::print("\x1b[");
  if (style != Normal) {
    n += EPrint::print((uint8)style, DEC);
    n += EPrint::print(';');
  }
  if (color != NoColor) {
    n += EPrint::print((uint8)color + 30, DEC);
    n += EPrint::print(';');
  }
  if (color != NoColor) {
    n += EPrint::print((uint8)background + 40, DEC);
  }

  n += EPrint::print('m');
  return n;
}

size_t EIO::end() { return EPrint::print("\x1b[0m"); }

size_t EIO::print(const EString &x, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EIO::print(char x, Style style, Color color, Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print((char)x);
  n += end();
  return n;
}

size_t EIO::print(const char x[], Style style, Color color, Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EIO::print(uint8 x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(int x, int base, Style style, Color color, Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(unsigned int x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(long x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(unsigned long x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(long long x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(unsigned long long x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(double x, int base, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EIO::print(const __FlashEStringHelper *x, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EIO::print(const EPrintable &x, Style style, Color color,
                  Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EIO::println(const EString &x, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(char x, Style style, Color color, Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(const char x[], Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(uint8 x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(int x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(unsigned int x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(long x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(unsigned long x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(long long x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(unsigned long long x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(double x, int base, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(const __FlashEStringHelper *x, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EIO::println(const EPrintable &x, Style style, Color color,
                    Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}
