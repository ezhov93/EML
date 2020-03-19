/*
 * @file   ewatchdoginterupt.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Watchdog with interupt source file.
 */

#include "ewatchdoginterupt.h"
#include "MDR32F9Qx_config.h"   // Keil::Device:Startup
#include "MDR32F9Qx_rst_clk.h"  // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_wwdg.h"     // Keil::Drivers:IWDG

static __IO uint32 Counter = 0;
static __IO argFunc_ptr Handler = null;
static void* Context = null;

EWatchdogInterupt& EWatchdogInterupt::instance() {
  static EWatchdogInterupt inst;
  return inst;
}

uint32 EWatchdogInterupt::tiks() const { return Counter; }

void EWatchdogInterupt::setTiks(int ticks) { Counter = ticks; }

void EWatchdogInterupt::attach(argFunc_ptr event, void* context) {
  Handler = event;
  Context = context;
}

void EWatchdogInterupt::deattach() { Handler = null; }

void EWatchdogInterupt::begin() { begin(Counter, _div); }

void EWatchdogInterupt::begin(int ticks, Prescaler div) {
  _div = div;
  Counter = ticks;
  _active = true;

  RST_CLK_PCLKcmd(RST_CLK_PCLK_WWDG, ENABLE);
  NVIC_EnableIRQ(WWDG_IRQn);
  WWDG_SetPrescaler(div);
  WWDG_SetWindowValue(Counter);
  WWDG_EnableIT();
  WWDG_Enable(Counter);
}

void EWatchdogInterupt::refresh() { WWDG_SetCounter(Counter); }

#ifdef __cplusplus
extern "C" {
#endif
void WWDG_IRQHandler(void) {
  WWDG_ClearFlag();
  if (Handler != null) Handler(Context);
}
#ifdef __cplusplus
}
#endif
