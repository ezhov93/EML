/*
 * @file   time.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timing and delay functions.
 */
 
#ifndef ETIME_H
#define ETIME_H

#include "etypes.h"
#include "einterrupts_private.h"

uint32 millis(void);
uint32 micros(void);
void delay(uint32 ms);
void delayMicroseconds(uint32 us);

#endif // ETIME_H
