/*
 * @file   ewatchdog.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Watchdog source file.
 */

#include "ewatchdog.h"
#include "MDR32F9Qx_config.h"   // Keil::Device:Startup
#include "MDR32F9Qx_iwdg.h"     // Keil::Drivers:IWDG
#include "MDR32F9Qx_rst_clk.h"  // Keil::Drivers:RST_CLK
#include "einterrupts.h"        // for noInterrupts(), interrupts()

#define RELOAD_MASK 0x0FFF

EWatchdog::EWatchdog(Interval interval) {
  RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG, ENABLE);
  IWDG_WriteAccessEnable();
  _interval_ptr = &MDR_IWDG->RLR;
  *_interval_ptr = interval;
  IWDG_SetPrescaler(IWDG_Prescaler_64);
  while (IWDG_GetFlagStatus(IWDG_FLAG_PVU) != 1)
    ;
  IWDG_WriteAccessDisable();
}

EWatchdog::Interval EWatchdog::interval() const {
  return (Interval)((*_interval_ptr) & RELOAD_MASK);
}

int EWatchdog::intervalToInt() const {
  return ((*_interval_ptr) & RELOAD_MASK) * 64;
}

void EWatchdog::setInterval(Interval interval) {
  IWDG_WriteAccessEnable();
  *_interval_ptr = interval;
  IWDG_WriteAccessDisable();
}

void EWatchdog::begin() { begin((Interval)((*_interval_ptr) & RELOAD_MASK)); }

void EWatchdog::begin(Interval time) {
  setInterval(time);
  IWDG_Enable();
  _active = true;
}

void EWatchdog::refresh() { IWDG_ReloadCounter(); }
