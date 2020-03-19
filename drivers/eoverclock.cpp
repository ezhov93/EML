/*
 * @file   eoverclock.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Overclock source file.
 */

#include "eoverclock.h"
#include <math.h>
#include "MDR32F9Qx_bkp.h"
#include "MDR32F9Qx_config.h"  // Keil::Device:Startup
#include "MDR32F9Qx_eeprom.h"
#include "MDR32F9Qx_rst_clk.h"  // Keil::Drivers:RST_CLK
#include "econfig.h"

void setCoreClock(float mhz) {
  uint32 mull = (mhz * 1000000) / HSE_Value;
  RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK, ENABLE);
  RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() == SUCCESS) {
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, mull - 1);
    RST_CLK_CPU_PLLcmd(ENABLE);
    if (RST_CLK_HSEstatus() == SUCCESS) {
      RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
      RST_CLK_CPU_PLLuse(ENABLE);
      RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
    }
  }

  RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
  EEPROM_SetLatency((uint32)(floor(mhz / 25) * 0x8));
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, DISABLE);

  Config_Time_setup();
}
