/*
 * @file   etime.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Delay implementation.
 */

#include "etime.h"
#include "einterrupts_private.h"
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup

inline uint32 millis() {
	return msec;
}

uint32 micros() {
  uint32 ms = millis();
  uint32 us = SysTick->VAL;
  return (ms * 1000)+SysTick->VAL;
}

void delay(uint32 ms) {
  uint32 time = millis()+ms;
  while(millis() != time);
}

void delayMicroseconds(uint32 us) {
  uint32 time = micros()+us;
  while(micros() != time);
}
