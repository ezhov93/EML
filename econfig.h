#ifndef ECONFIG_H
#define ECONFIG_H

#include "MDR1986VE1T.h"
#include "MDR32F9Qx_config.h"

#define TIMER

// Core clock
#define CONFIG_CORE_CLOCK (SystemCoreClock)
static void Config_restart() { NVIC_SystemReset(); }

// Main timer intialize
#ifdef TIMER
#define CONFIG_TIME_HANDLER TIMER1_IRQHandler
#define CONFIG_TIME_VAL MDR_TIMER1->CNT
static void Config_Time_setup() {
  SystemCoreClockUpdate();
  MDR_RST_CLK->PER_CLOCK |= 0x0004000;
  MDR_RST_CLK->TIM_CLOCK = 0x01000000;
  MDR_TIMER1->CNT = 0;
  MDR_TIMER1->ARR = SystemCoreClock / 1000 - 1;
  MDR_TIMER1->IE = 0x2;
  MDR_TIMER1->CNTRL = 0x0001;
  NVIC_EnableIRQ(TIMER1_IRQn);
}
static void Config_Time_clear() { MDR_TIMER1->STATUS &= 0xFFFD; }
#else
#define CONFIG_TIME_HANDLER SysTick_Handler
#define CONFIG_TIME_VAL SysTick->VAL
static void Config_Time_setup() {
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 1000 - 1);
}
static void Config_Time_clear() { NVIC_ClearPendingIRQ(SysTick_IRQn); }
#endif

#endif  // ECONFIG_H
