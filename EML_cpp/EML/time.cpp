/*
 * @file   time.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Delay implementation.
 */

#include "time.h"

uint32 millis() {
	return 
}

uint32 micros() {
    uint32 ms;
    uint32 cycle_cnt;

    do {
        ms = millis();
        cycle_cnt = systick_get_count();
        asm volatile("nop"); //allow interrupt to fire
        asm volatile("nop");
    } while (ms != millis());

#define US_PER_MS               1000
    return ((ms * US_PER_MS) +
            (SYSTICK_RELOAD_VAL + 1 - cycle_cnt) / CYCLES_PER_MICROSECOND);
#undef US_PER_MS
}

void delay(uint32 ms) {
    uint32 start = micros();
    while (ms > 0)    {
        while ( (ms > 0) && ((micros() - start) >= 1000) )        {
            ms--;
            start += 1000;
        }
    }
}

void delayMicroseconds(uint32 us) {
    delay_us(us);
}
