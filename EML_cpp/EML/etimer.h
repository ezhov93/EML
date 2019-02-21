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
    int _timerId;
    void *_timer_ptr;
    func_ptr _handler;
    int _interval;
    bool _singleShot;
    int _irq;
    int _div;
    int _rate;    
  
  public:
    enum Type { MSEC = 1000, USEC = MSEC*1000} _type;
    ETimer(int timerId, Type type);
    Type type() const;
    void setType(Type type);
    int interval() const;
    bool isActive() const;
    bool isSingleShot() const;
    void setSingleShot(bool singleShot);
    void setInterval(int msec);
    void start();
    void start(int msec);
    void pause(void);
    void resume(void);
    int remaningTime() const;
    // void attachInterrupt(int channel, func_ptr handler);
    // void detachInterrupt(int channel); 
    void attachInterrupt(func_ptr handler);
    void detachInterrupt();
};

#endif
