/*
 * @file   etime.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Delay implementation.
 */

#include "etime.h"
#include "econfig.h"
#include "epio.h"

__IO static uint32 msec = 0;

uint32 millis() { return msec; }

uint32 micros() {
  uint32 ms = millis();
  uint32 us = (CONFIG_TIME_VAL / 1000) - 1;
  return (ms * 1000) + us;
}

void delay(int ms) {
  uint32 timer = millis();
  while (millis() - timer < ms)
    ;
}

void delayMicroseconds(int us) {
  uint32 timer = micros();
  while (micros() - timer < us)
    ;
}

#ifdef __cplusplus
extern "C" {
#endif
void CONFIG_TIME_HANDLER() {
  Config_Time_clear();
  ++msec;
}
#ifdef __cplusplus
}
#endif
