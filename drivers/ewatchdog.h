/*
 * @file   etime.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Watchdog class.
 */

#ifndef EWATCHDOG_H
#define EWATCHDOG_H

#include "etypes.h"

class EWatchdog {
 public:
  enum Interval {
    MSEC16 = 5,
    MSEC32 = 10,
    MSEC64 = 20,
    MSEC128 = 40,
    MSEC256 = 60,
    MSEC512 = 120,
    SEC1 = 240,
    SEC2 = 480,
    SEC4 = 960,
    SEC8 = 1920,
  };
  EWatchdog(Interval interval = SEC8);
  Interval interval() const;
  int intervalToInt() const;
  bool isActive() const { return _active; }
  void setInterval(Interval);
  void begin();
  void begin(Interval);
  void refresh();

 private:
  __IO uint32 *_interval_ptr;
  bool _active;
};

#endif  // EWATCHDOG_H
