/*
 * @file   etimer.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timer class.
 */

#ifndef ETIMER_H_
#define ETIMER_H_

#include "etypes.h"

 
class ETimer {
  private:
    uint32 timerId;
    void *timer_ptr;
    func_ptr handler;
  
  public:
    ETimer(uint8 timerId);
    int interval() const;
    bool isActive() const;
    bool isSingleShot() const;
    void setInterval(int msec);
    void start();
    void start(int msec);
    void pause(void);
    void resume(void);
    void reset();
    int remaningTime();
    // void attachInterrupt(int channel, func_ptr handler);
    // void detachInterrupt(int channel); 
    void attachInterrupt(func_ptr handler);
    void detachInterrupt();
};

#endif
