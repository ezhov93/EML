/*
 * @file  esturtup.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Startup file.
 */

#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

#define ALL_PORTS_CLK                                             \
  (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | \
   RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

void disableAllPorts() {
  /*
          RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);
          PORT_InitTypeDef PORT_InitStructure;

          PORT_StructInit(&PORT_InitStructure);
          PORT_Init(MDR_PORTA, &PORT_InitStructure);
          PORT_Init(MDR_PORTB, &PORT_InitStructure);
          PORT_Init(MDR_PORTC, &PORT_InitStructure);
          PORT_Init(MDR_PORTD, &PORT_InitStructure);
          PORT_Init(MDR_PORTE, &PORT_InitStructure);
          PORT_Init(MDR_PORTF, &PORT_InitStructure);

          RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
   */
}

void disableAllInterupts() {
#if defined(USE_MDR1986VE9x)
  SCB->AIRCR = 0x05FA0000 | ((uint32_t)0x500);
  SCB->VTOR = 0x08000000;
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICER[0] = 0xFFFFFFFF;
#endif
}

void systickSetup() {
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 1000);
}
