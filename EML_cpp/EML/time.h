/*
 * @file   time.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timing and delay functions.
 */
 
#ifndef ETIME_H
#define ETIME_H


#include <boards.h>

/**
 * Returns time (in milliseconds) since the beginning of program
 * execution. On overflow, restarts at 0.
 * @see micros()
 */
uint32 millis(void);
/**
 * Returns time (in microseconds) since the beginning of program
 * execution.  On overflow, restarts at 0.
 * @see millis()
 */
uint32 micros(void) {
    uint32 ms;
    uint32 cycle_cnt;

    do {
        ms = millis();
        cycle_cnt = systick_get_count();
        asm volatile("nop"); //allow interrupt to fire
        asm volatile("nop");
    } while (ms != millis());

#define US_PER_MS               1000
    /* SYSTICK_RELOAD_VAL is 1 less than the number of cycles it
     * actually takes to complete a SysTick reload */
    return ((ms * US_PER_MS) +
            (SYSTICK_RELOAD_VAL + 1 - cycle_cnt) / CYCLES_PER_MICROSECOND);
#undef US_PER_MS
}

/**
 * Delay for at least the given number of milliseconds.
 *
 * Interrupts, etc. may cause the actual number of milliseconds to
 * exceed ms.  However, this function will return no less than ms
 * milliseconds from the time it is called.
 *
 * @param ms the number of milliseconds to delay.
 * @see delayMicroseconds()
 */
void delay(unsigned long ms);

/**
 * Delay for at least the given number of microseconds.
 *
 * Interrupts, etc. may cause the actual number of microseconds to
 * exceed us.  However, this function will return no less than us
 * microseconds from the time it is called.
 *
 * @param us the number of microseconds to delay.
 * @see delay()
 */
void delayMicroseconds(uint32 us);

#endif // ETIME_H
