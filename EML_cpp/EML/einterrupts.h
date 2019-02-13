/*
 * @file   einterupts.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Interrupt prototypes and types.
 */

#ifndef EINTERRUPTS_H
#define EINTERRUPTS_H

/**
 * The kind of transition on an external pin which should trigger an
 * interrupt.
 */
typedef enum ExtIntTriggerMode {
    RISING, /**< To trigger an interrupt when the pin transitions LOW
                 to HIGH */
    FALLING, /**< To trigger an interrupt when the pin transitions
                  HIGH to LOW */
    CHANGE /**< To trigger an interrupt when the pin transitions from
                LOW to HIGH or HIGH to LOW (i.e., when the pin
                changes). */
} ExtIntTriggerMode;

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Function to run upon external interrupt trigger.
 *                 The handler should take no arguments, and have void
 *                 return type.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode);

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Static class member function to run upon external interrupt
 *                 trigger. The handler should take 1 argument and return void
 *  @param arg Argument that the handler will be passed when it's called. One
 *             use of this is to pass the specific instance of the class that
 *             will handle the interrupt.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
void attachInterrupt(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode);

/**
 * @brief Disable any registered external interrupt.
 * @param pin Maple pin number
 * @sideeffect unregisters external interrupt handler
 * @see attachInterrupt()
 */
void detachInterrupt(uint8 pin);

/**
 * Re-enable interrupts.
 *
 * Call this after noInterrupts() to re-enable interrupt handling,
 * after you have finished with a timing-critical section of code.
 *
 * @see noInterrupts()
 */
static inline __always_inline void interrupts() {
    nvic_globalirq_enable();
}

/**
 * Disable interrupts.
 *
 * After calling this function, all user-programmable interrupts will
 * be disabled.  You can call this function before a timing-critical
 * section of code, then call interrupts() to re-enable interrupt
 * handling.
 *
 * @see interrupts()
 */
static inline __always_inline void noInterrupts() {
    nvic_globalirq_disable();
}

#endif

