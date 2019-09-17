/*
 * @file   ESoftTimer.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Soft timer class. Based on millis()/micros()
 */

#ifndef ESOFTTIMER_H
#define ESOFTTIMER_H

#include "ecore.h"

class ESoftTimer
{
  public:
    enum Type { MS = 1000, US = MS*1000};
    explicit ESoftTimer(uint32 interval = 1000, Type type = MS);		
    Type type() const;
    void setType(Type type);
    int interval() const;
    bool isActive() const;
    bool isReady();
    bool isSingleShot() const;
    void setSingleShot(bool singleShot = false);
    void setInterval(int interval);
    void start();
    void start(int interval);
    void pause();
    void resume();
    void reset();
    void update();
    int remaningTime() const;
    void attachEvent(func_ptr handler);
    void detachEvent();
    
  private:
    uint32 _timer;
    uint32 _interval;
    Type _type;
    uint32(*time)();
    func_ptr _handler;
    bool _isActive;
    bool _isReady;
    bool _singleShot;
};

#endif // ESOFTTIMER_H


