/*
 * @file   einterupts.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Private interface for interrupts.
 */

#include "einterrupts_private.h"

#ifdef __cplusplus
extern "C" {
#endif

void UART1_IRQHandler(void) { }
void UART2_IRQHandler(void) { }
void ADC_IRQHandler(void) { }

uint32 msec = 0;
void SysTick_Handler(void) {
  ++msec;
}

void BKP_IRQHandler(void)	{
}


#ifdef __cplusplus
}
#endif