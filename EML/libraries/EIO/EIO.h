/*
 * @file   EIO.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Console input/output helper header file.
 */

#ifndef EIO_H
#define EIO_H

#include "estream.h"

class EIO : private EStream {
 public:
  enum Key : char { Key_Normal };
  enum Style : char {
    Normal,
    Bold,
    Underlined = 4,
    Flashing = 5,
    Inverted = 7,
    Invisible = 8,
    NoStyle
  };

  enum Color : char {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    BlueLight,
    White,
    NoColor
  };

  EIO(EStream *parent) { _parent = parent; }
  EString scan();
  void scan(char *);

  using EStream::print;
  size_t print(const EString &, Style, Color = White, Color background = Black);
  size_t print(char, Style, Color = White, Color background = Black);
  size_t print(const char[], Style, Color = White, Color background = Black);
  size_t print(uint8, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(int, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(unsigned int, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(long, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(unsigned long, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(long long, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(unsigned long long, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(double, int base, Style = Normal, Color = White,
               Color background = Black);
  size_t print(const __FlashEStringHelper *, Style, Color = White,
               Color background = Black);
  size_t print(const EPrintable &, Style, Color = White,
               Color background = Black);
  using EStream::println;
  size_t println(const EString &s, Style, Color = White,
                 Color background = Black);
  size_t println(char, Style, Color = White, Color background = Black);
  size_t println(const char[], Style, Color = White, Color background = Black);
  size_t println(uint8, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(int, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(unsigned int, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(long, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(unsigned long, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(long long, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(unsigned long long, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(double, int base, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(const __FlashEStringHelper *, Style = Normal, Color = White,
                 Color background = Black);
  size_t println(const EPrintable &, Style = Normal, Color = White,
                 Color background = Black);

 private:
  EStream *_parent;
  size_t begin(Style, Color, Color background);
  size_t end();
  virtual int available(void) { return _parent->available(); }
  virtual int peek(void) { return _parent->peek(); }
  virtual void flush(void) { _parent->flush(); }
  using EStream::write;
  virtual size_t write(uint8 ch) {
    _parent->write(ch);
    _parent->flush();
    return 1;
  }
  virtual int read(void);
};

#endif  // EIO_H
