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
#include "etime.h"

/* eCore macros*/


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
void restart();

#endif // ECORE_H

