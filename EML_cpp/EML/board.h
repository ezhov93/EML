/*
 * @file  board.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Board header
 */

#ifndef _BOARD_GENERIC_STM32F103C_H_
#define _BOARD_GENERIC_STM32F103C_H_

#define CYCLES_PER_MICROSECOND	(F_CPU / 1000000U)
#define SYSTICK_RELOAD_VAL     (F_CPU/1000) - 1 /* takes a cycle to reload */

#define BOARD_NR_USARTS           3
#define BOARD_USART1_TX_PIN       PA9
#define BOARD_USART1_RX_PIN       PA10
#define BOARD_USART2_TX_PIN       PA2
#define BOARD_USART2_RX_PIN       PA3

#define BOARD_NR_SPI              2
#define BOARD_SPI1_NSS_PIN        PA4
#define BOARD_SPI1_MOSI_PIN       PA7
#define BOARD_SPI1_MISO_PIN       PA6
#define BOARD_SPI1_SCK_PIN        PA5

#define BOARD_SPI2_NSS_PIN        PB12
#define BOARD_SPI2_MOSI_PIN       PB15
#define BOARD_SPI2_MISO_PIN       PB14
#define BOARD_SPI2_SCK_PIN        PB13

#define BOARD_NR_GPIO_PINS        35
#define BOARD_NR_PWM_PINS         12
#define BOARD_NR_ADC_PINS          9
#define BOARD_NR_USED_PINS         4

// Note this needs to match with the PIN_MAP array in board.cpp
enum {
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,PA14,PA15,
	PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,PB14,PB15,
	PC13, PC14,PC15
}PinMap;

#endif
