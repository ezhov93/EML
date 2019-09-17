/*
 * @file   einterupts.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Interrupt prototypes and types.
 */

#ifndef EINTERRUPTS_H
#define EINTERRUPTS_H

#include "etypes.h"

typedef enum Interrupt {
    RISING, /**< To trigger an interrupt when the pin transitions LOW
                 to HIGH */
    FALLING, /**< To trigger an interrupt when the pin transitions
                  HIGH to LOW */
    CHANGE /**< To trigger an interrupt when the pin transitions from
                LOW to HIGH or HIGH to LOW (i.e., when the pin
                changes). */
} Interrupt;


void attachInterrupt(int pin, Interrupt interrupt, func_ptr handler);
void attachInterrupt(int pin, Interrupt interrupt, argFunc_ptr handler, void *arg);
void detachInterrupt(int pin);
void interrupts();
void noInterrupts();

#endif

