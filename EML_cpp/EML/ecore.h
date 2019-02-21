/*
 * @file   ecore.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main include file for the Wirish core.
 */

#ifndef ECORE_H
#define ECORE_H

/* Includes */
#include "enew.h"
#include "ebits.h"
#include "etypes.h"
#include "epio.h"
#include "echar.h"
#include "emath.h"
//#include <cmath>
#include "etime.h"
// #include "itoa.h"

/* eCore macros*/
#define lowByte(w)                     ((w) & 0xFF)
#define highByte(w)                    (((w) >> 8) & 0xFF)
#define bitRead(value, bit)            (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)             ((value) |= (1UL << (bit)))
#define bitClear(value, bit)           ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : \
                                                   bitClear(value, bit))
#define bit(b)                         (1UL << (b))

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif 

/*
#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )
*/

#define digitalPinToInterrupt(pin) (pin)

/* eCore main state functions */
void setup();
void loop();

void setCoreClock(float mhz);
float coreClock();

#endif // ECORE_H

