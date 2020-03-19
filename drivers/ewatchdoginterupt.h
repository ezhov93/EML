/*
 * @file   ewatchdoginterupt.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Watchdog whith interupt class.
 */

#ifndef EWATCHDOGINTERUPT_H
#define EWATCHDOGINTERUPT_H

#include "ecore.h"

class EWatchdogInterupt {
  EWatchdogInterupt() : _active(false) {}

 public:
  enum Prescaler {
    Prescaler1 = 0,
    Prescaler2 = 0x80,
    Prescaler4 = 0x100,
    Prescaler8 = 0x180,
  };

  static EWatchdogInterupt& instance();
  uint32 tiks() const;
  bool isActive() const { return _active; }
  void setTiks(int ticks);
  void setPrescaler(Prescaler div) { _div = div; }
  void begin();
  void begin(int ticks, Prescaler div = Prescaler8);
  void refresh();
  void attach(argFunc_ptr, void*);
  void deattach();

 private:
  bool _active;
  Prescaler _div;
};

#endif  // EWATCHDOGINTERUPT_H
