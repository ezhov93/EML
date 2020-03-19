/*
 * @file   etimer.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timer class.
 */

#ifndef ETIMER_H_
#define ETIMER_H_

#include "etypes.h"

class ETimer {
 public:
  enum Type { MS = 1000, US = MS * 1000 };
  ETimer(int timerId, Type type = MS);
  Type type() const;
  void setType(Type type);
  int interval() const;
  bool isActive() const;
  bool isReady() const;
  bool isSingleShot() const;
  void setSingleShot(bool singleShot = false);
  void setInterval(int time);
  void start();
  void start(int time);
  void pause();
  void resume();
  void reset();
  int remaningTime() const;
  // void attachInterrupt(int channel, func_ptr handler);
  // void detachInterrupt(int channel);
  void attachInterrupt(func_ptr handler);
  void detachInterrupt();

 private:
  int _timerId;
  void *_timer_ptr;
  func_ptr _handler;
  Type _type;
  __IO uint32 *_interval_ptr;
  bool _singleShot;
  int _irq;
  int _div;
  int _rate;
};

#endif
