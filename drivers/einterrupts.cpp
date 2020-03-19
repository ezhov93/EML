/*
 * @file   einterupts.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Interface for interrupts.
 */

#include "einterrupts.h"
#include "MDR32F9Qx_config.h"  // Keil::Device:Startup

void attachInterrupt(int pin, func_ptr handler, Interrupt interrupt) {
  if (!handler) return;
  /*  exti_attach_interrupt((exti_num)(PIN_MAP[pin].gpio_bit),
                          gpio_exti_port(PIN_MAP[pin].gpio_device),
                          handler,
                          outMode);*/
}

void attachInterrupt(int pin, argFunc_ptr handler, void *arg,
                     Interrupt interrupt) {
  if (!handler) return;
  /* exti_attach_callback((exti_num)(PIN_MAP[pin].gpio_bit),
                         gpio_exti_port(PIN_MAP[pin].gpio_device),
                         handler,
                         arg,
                         outMode);*/
}

void detachInterrupt(int pin) {
  /* exti_detach_interrupt((exti_num)(PIN_MAP[pin].gpio_bit));*/
}

inline __always_inline void interrupts() { __enable_irq(); }
inline __always_inline void noInterrupts() { __disable_irq(); }
