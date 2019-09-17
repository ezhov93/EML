/*
 * @file   EMonitor.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Console input/output helper source file.
 */

#include "EMonitor.h"
#include "echar.h"

EString EMonitor::scan() {
  EString ret;
  uint32 temp = _timeout;
  setTimeout(10);
  int cnt = 0;
  print('>');
  while (true) {
    if (_parent->available() > 0) {
      EString cmd = readString();
      if (isControl(cmd.charAt(0))) {
        if (cmd.startsWith("\r")) break;
        if (!ret.length()) continue;
        if (cmd == "\x1b[D") {
          if (cnt > 0)
            --cnt;
          else
            continue;
        } else if (cmd == "\x1b[C") {
          if (cnt < ret.length())
            cnt++;
          else
            continue;
        } else if (cmd.charAt(0) == 127) {  // backspace
          ret.remove(--cnt, 1);
          int length = ret.length();
          if (length != cnt) {
            ++length;
            while (length--) print(' ');
            print("\r>");
            print(ret);
            int shift = ret.length() - cnt;
            while (shift--) print("\x1b[D");
            continue;
          }
        } else
          continue;
        print(cmd);
      } else if (isPrintable(cmd.charAt(0))) {
        if (cnt == ret.length())
          ret += cmd;
        else
          ret.setCharAt(cnt, cmd.charAt(0));
        ++cnt;
        print(cmd);
      }
    }
  }
  println();
  setTimeout(temp);
  return ret;
}

void EMonitor::scan(char *str) {
  char *ret;
  int c = read();
  while (true) {
    if (c >= 0) {
      char ch = (char)c;
      if (ch == '\r' || ch == '\n') break;
      if (isPrintable(ch)) *ret++ = ch;
    }
    c = read();
  }
  println();
}

int EMonitor::read() {
  int ch = _parent->read();
  return ch;
}

size_t EMonitor::begin(Style style, Color color, Color background) {
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

size_t EMonitor::end() { return EPrint::print("\x1b[0m"); }

size_t EMonitor::print(const EString &x, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EMonitor::print(char x, Style style, Color color, Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print((char)x);
  n += end();
  return n;
}

size_t EMonitor::print(const char x[], Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EMonitor::print(uint8 x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(int x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(unsigned int x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(long x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(unsigned long x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(long long x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(unsigned long long x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(double x, int base, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x, base);
  n += end();
  return n;
}

size_t EMonitor::print(const __FlashEStringHelper *x, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EMonitor::print(const EPrintable &x, Style style, Color color,
                       Color background) {
  size_t n = begin(style, color, background);
  n += EPrint::print(x);
  n += end();
  return n;
}

size_t EMonitor::println(const EString &x, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(char x, Style style, Color color, Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(const char x[], Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(uint8 x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(int x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(unsigned int x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(long x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(unsigned long x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(long long x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(unsigned long long x, int base, Style style,
                         Color color, Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(double x, int base, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(const __FlashEStringHelper *x, Style style,
                         Color color, Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}

size_t EMonitor::println(const EPrintable &x, Style style, Color color,
                         Color background) {
  size_t n = print(x, style, color, background);
  n += EPrint::println();
  return n;
}
