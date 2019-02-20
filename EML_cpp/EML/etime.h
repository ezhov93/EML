/*
 * @file   time.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timing and delay functions.
 */
 
#ifndef ETIME_H
#define ETIME_H

#include "etypes.h"

uint32 millis(void);
uint32 micros(void);
void delay(int ms);
void delayMicroseconds(int us);

#endif // ETIME_H
