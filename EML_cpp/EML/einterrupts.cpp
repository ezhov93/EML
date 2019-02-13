/*
 * @file   einterupts.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Interface for interrupts.
 */

/**
 * @file wirish/ext_interrupts.cpp
 * @brief Wiring-like interface for external interrupts
 */

#include "interrupts.h"


static inline exti_trigger_mode exti_out_mode(ExtIntTriggerMode mode);

void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode) {
    if (!handler) return;
    exti_attach_interrupt((exti_num)(PIN_MAP[pin].gpio_bit),
                          gpio_exti_port(PIN_MAP[pin].gpio_device),
                          handler,
                          outMode);
}

void attachInterrupt(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode) {
    if (!handler)	return;
    exti_attach_callback((exti_num)(PIN_MAP[pin].gpio_bit),
                          gpio_exti_port(PIN_MAP[pin].gpio_device),
                          handler,
                          arg,
                          outMode);
}

void detachInterrupt(uint8 pin) {
    exti_detach_interrupt((exti_num)(PIN_MAP[pin].gpio_bit));
}

#ifdef __cplusplus
extern "C" {
#endif

void UART1_IRQHandler(void) { }
void UART2_IRQHandler(void) { }
void ADC_IRQHandler(void) { }

void SysTick_Handler(void) {
}

void BKP_IRQHandler(void)	{
  if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_SECF) == SET)
  {
    BKP_RTC_ITConfig(BKP_RTC_IT_SECF, DISABLE);


    BKP_RTC_ITConfig(BKP_RTC_IT_SECF, ENABLE);
  }
}





#ifdef __cplusplus
}
#endif