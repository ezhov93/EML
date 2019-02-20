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
    uint32 number = 0;
  
  public:
    ETimer(uint8 number);
    void pause(void);
    void resume(void);
    uint32 getPrescaleFactor();
    void setPrescaleFactor(uint32 factor);
    uint16 getOverflow();
    void setOverflow(uint16 val);
    uint16 getCount(void);
    void setCount(uint16 val);
    uint16 setPeriod(uint32 microseconds);
    void setMode(int channel, timer_mode mode);
    uint16 getCompare(int channel);
    void setCompare(int channel, uint16 compare);
    void attachInterrupt(int channel, voidFuncPtr handler);
    void detachInterrupt(int channel);
    void refresh(void);    
  }

#endif
