/*
 * @file  main.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main file.
 */
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

#define ALL_PORTS_CLK (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                       RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                       RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)
 
extern void setup(void);
extern void loop(void);

void setupPorts(void) {
	RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);
	PORT_InitTypeDef PORT_InitStructure;
	/* Configure all ports to the state as after reset, i.e. low power consumption */
	PORT_StructInit(&PORT_InitStructure);
	PORT_Init(MDR_PORTA, &PORT_InitStructure);
	PORT_Init(MDR_PORTB, &PORT_InitStructure);
	PORT_Init(MDR_PORTC, &PORT_InitStructure);
	PORT_Init(MDR_PORTD, &PORT_InitStructure);
	PORT_Init(MDR_PORTE, &PORT_InitStructure);
	PORT_Init(MDR_PORTF, &PORT_InitStructure);

	/* Disable the RTCHSE clock on all ports */
	RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
}


int main(void) {
	setupPorts();
	
	setup();
	while (1)
		loop();
}
