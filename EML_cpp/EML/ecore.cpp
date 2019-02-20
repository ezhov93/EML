/*
 * @file   ecore.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main include file.
 */

#include "ecore.h"
#include "MDR32F9Qx_config.h" 
#include "MDR32F9Qx_rst_clk.h" 

void setCoreClock(int mhz) {
  uint32 mull = (mhz * 1000000)/HSE_Value;
  RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() == SUCCESS) {
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, mull);
    RST_CLK_CPU_PLLcmd(ENABLE);
    if (RST_CLK_HSEstatus() == SUCCESS) {
      RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
      RST_CLK_CPU_PLLuse(ENABLE);
      RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
    }
  }
  SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}	

inline uint32 coreClock() {
  return SystemCoreClock;
}

