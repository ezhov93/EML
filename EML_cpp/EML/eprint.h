/*
 * @file  eprint.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Base class that provides print() and println().
 */

#ifndef EPRINT_H_
#define EPRINT_H_

#include "estring.h"
#include "eprintable.h"

class Print {
public:
  enum {
    BIN  = 2,
    OCT  = 8,
    DEC  = 10,
    HEX  = 16
  };
  
  virtual size_t write(uint8 ch) = 0;
  virtual size_t write(const char *str);
  virtual size_t write(const void *buf, uint32 len);
	
	size_t print(const String &);
    size_t print(char);
    size_t print(const char[]);
    size_t print(uint8, int=DEC);
    size_t print(int, int=DEC);
    size_t print(unsigned int, int=DEC);
    size_t print(long, int=DEC);
    size_t print(unsigned long, int=DEC);
    size_t print(long long, int=DEC);
    size_t print(unsigned long long, int=DEC);
    size_t print(double, int=2);
    size_t print(const __FlashStringHelper *);
    size_t print(const EPrintable&);
    size_t println(void);
	size_t println(const String &s);
	size_t println(char);
	size_t println(const char[]);
    size_t println(uint8, int=DEC);
    size_t println(int, int=DEC);
    size_t println(unsigned int, int=DEC);
    size_t println(long, int=DEC);
    size_t println(unsigned long, int=DEC);
    size_t println(long long, int=DEC);
    size_t println(unsigned long long, int=DEC);
    size_t println(double, int=2);
    size_t println(const __FlashStringHelper *);
    size_t println(const EPrintable&);

    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }
	
  protected:
    void setWriteError(int err = 1) { write_error = err; }

private:
	int write_error;
    size_t printNumber(unsigned long long, uint8);
    size_t printFloat(double, uint8);
};

#endif
