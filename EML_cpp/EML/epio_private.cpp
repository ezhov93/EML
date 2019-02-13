/*
 * @file   epin_private.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Private pin file.
 */
 
#include "epio_private.h"

const PinMap pinMap[] =  {
    {MDR_PORTA, PORT_Pin_0,  NONE, NONE},  /* PA0 */
    {MDR_PORTA, PORT_Pin_1,  NONE, NONE},  /* PA1 */
    {MDR_PORTA, PORT_Pin_2,  NONE, NONE},  /* PA2 */
    {MDR_PORTA, PORT_Pin_3,  NONE, NONE},  /* PA3 */
    {MDR_PORTA, PORT_Pin_4,  NONE, NONE},  /* PA4 */
    {MDR_PORTA, PORT_Pin_5,  NONE, NONE},  /* PA5 */
    {MDR_PORTA, PORT_Pin_6,  NONE, NONE},  /* PA6 */
    {MDR_PORTA, PORT_Pin_7,  NONE, NONE},  /* PA7 */
    {MDR_PORTA, PORT_Pin_8,  NONE, NONE},  /* PA8 */
    {MDR_PORTA, PORT_Pin_9,  NONE, NONE},  /* PA9 */
    {MDR_PORTA, PORT_Pin_10, NONE, NONE},  /* PA10 */
    {MDR_PORTA, PORT_Pin_11, NONE, NONE},  /* PA11 */
    {MDR_PORTA, PORT_Pin_12, NONE, NONE},  /* PA12 */
    {MDR_PORTA, PORT_Pin_13, NONE, NONE},  /* PA13 */
    {MDR_PORTA, PORT_Pin_14, NONE, NONE},  /* PA14 */
    {MDR_PORTA, PORT_Pin_15, NONE, NONE},  /* PA15 */
    {MDR_PORTB, PORT_Pin_0,  NONE, NONE},  /* PB0 */
    {MDR_PORTB, PORT_Pin_1,  NONE, NONE},  /* PB1 */
    {MDR_PORTB, PORT_Pin_2,  NONE, NONE},  /* PB2 */
    {MDR_PORTB, PORT_Pin_3,  NONE, NONE},  /* PB3 */
    {MDR_PORTB, PORT_Pin_4,  NONE, NONE},  /* PB4 */
    {MDR_PORTB, PORT_Pin_5,  NONE, NONE},  /* PB5 */
    {MDR_PORTB, PORT_Pin_6,  NONE, NONE},  /* PB6 */
    {MDR_PORTB, PORT_Pin_7,  NONE, NONE},  /* PB7 */
    {MDR_PORTB, PORT_Pin_8,  NONE, NONE},  /* PB8 */
    {MDR_PORTB, PORT_Pin_9,  NONE, NONE},  /* PB9 */
    {MDR_PORTB, PORT_Pin_10, NONE, NONE},  /* PB10 */
    {MDR_PORTB, PORT_Pin_11, NONE, NONE},  /* PB11 */
    {MDR_PORTB, PORT_Pin_12, NONE, NONE},  /* PB12 */
    {MDR_PORTB, PORT_Pin_13, NONE, NONE},  /* PB13 */
    {MDR_PORTB, PORT_Pin_14, NONE, NONE},  /* PB14 */
    {MDR_PORTB, PORT_Pin_15, NONE, NONE},  /* PB15 */
    {MDR_PORTC, PORT_Pin_0,  NONE, NONE},  /* PC0 */
    {MDR_PORTC, PORT_Pin_1,  NONE, NONE},  /* PC1 */
    {MDR_PORTC, PORT_Pin_2,  NONE, NONE},  /* PC2 */
    {MDR_PORTC, PORT_Pin_3,  NONE, NONE},  /* PC3 */
    {MDR_PORTC, PORT_Pin_4,  NONE, NONE},  /* PC4 */
    {MDR_PORTC, PORT_Pin_5,  NONE, NONE},  /* PC5 */
    {MDR_PORTC, PORT_Pin_6,  NONE, NONE},  /* PC6 */
    {MDR_PORTC, PORT_Pin_7,  NONE, NONE},  /* PC7 */
    {MDR_PORTC, PORT_Pin_8,  NONE, NONE},  /* PC8 */
    {MDR_PORTC, PORT_Pin_9,  NONE, NONE},  /* PC9 */
    {MDR_PORTC, PORT_Pin_10, NONE, NONE},  /* PC10 */
    {MDR_PORTC, PORT_Pin_11, NONE, NONE},  /* PC11 */
    {MDR_PORTC, PORT_Pin_12, NONE, NONE},  /* PC12 */
    {MDR_PORTC, PORT_Pin_13, NONE, NONE},  /* PC13 */
    {MDR_PORTC, PORT_Pin_14, NONE, NONE},  /* PC14 */
    {MDR_PORTC, PORT_Pin_15, NONE, NONE},  /* PC15 */
    {MDR_PORTD, PORT_Pin_0,     0, NONE},  /* PD0 */
    {MDR_PORTD, PORT_Pin_1,     1, NONE},  /* PD1 */
    {MDR_PORTD, PORT_Pin_2,     2, NONE},  /* PD2 */
    {MDR_PORTD, PORT_Pin_3,     3, NONE},  /* PD3 */
    {MDR_PORTD, PORT_Pin_4,     4, NONE},  /* PD4 */
    {MDR_PORTD, PORT_Pin_5,     5, NONE},  /* PD5 */
    {MDR_PORTD, PORT_Pin_6,     6, NONE},  /* PD6 */
    {MDR_PORTD, PORT_Pin_7,     7, NONE},  /* PD7 */
    {MDR_PORTD, PORT_Pin_8,     8, NONE},  /* PD8 */
    {MDR_PORTD, PORT_Pin_9,     9, NONE},  /* PD9 */
    {MDR_PORTD, PORT_Pin_10,   10, NONE},  /* PD10 */
    {MDR_PORTD, PORT_Pin_11,   11, NONE},  /* PD11 */
    {MDR_PORTD, PORT_Pin_12,   12, NONE},  /* PD12 */
    {MDR_PORTD, PORT_Pin_13,   13, NONE},  /* PD13 */
    {MDR_PORTD, PORT_Pin_14,   14, NONE},  /* PD14 */
    {MDR_PORTD, PORT_Pin_15,   15, NONE},  /* PD15 */
    {MDR_PORTE, PORT_Pin_0,  NONE,    2},  /* PE0 */
    {MDR_PORTE, PORT_Pin_1,  NONE, NONE},  /* PE1 */
    {MDR_PORTE, PORT_Pin_2,  NONE, NONE},  /* PE2 */
    {MDR_PORTE, PORT_Pin_3,  NONE, NONE},  /* PE3 */
    {MDR_PORTE, PORT_Pin_4,  NONE, NONE},  /* PE4 */
    {MDR_PORTE, PORT_Pin_5,  NONE, NONE},  /* PE5 */
    {MDR_PORTE, PORT_Pin_6,  NONE, NONE},  /* PE6 */
    {MDR_PORTE, PORT_Pin_7,  NONE, NONE},  /* PE7 */
    {MDR_PORTE, PORT_Pin_8,  NONE, NONE},  /* PE8 */
    {MDR_PORTE, PORT_Pin_9,  NONE,    1},  /* PE9 */
    {MDR_PORTE, PORT_Pin_10, NONE, NONE},  /* PE10 */
    {MDR_PORTE, PORT_Pin_11, NONE, NONE},  /* PE11 */
    {MDR_PORTE, PORT_Pin_12, NONE, NONE},  /* PE12 */
    {MDR_PORTE, PORT_Pin_13, NONE, NONE},  /* PE13 */
    {MDR_PORTE, PORT_Pin_14, NONE, NONE},  /* PE14 */
    {MDR_PORTE, PORT_Pin_15, NONE, NONE},  /* PE15 */
    {MDR_PORTF, PORT_Pin_1,  NONE, NONE},  /* PF0 */
    {MDR_PORTF, PORT_Pin_1,  NONE, NONE},  /* PF1 */
    {MDR_PORTF, PORT_Pin_2,  NONE, NONE},  /* PF2 */
    {MDR_PORTF, PORT_Pin_3,  NONE, NONE},  /* PF3 */
    {MDR_PORTF, PORT_Pin_4,  NONE, NONE},  /* PF4 */
    {MDR_PORTF, PORT_Pin_5,  NONE, NONE},  /* PF5 */
    {MDR_PORTF, PORT_Pin_6,  NONE, NONE},  /* PF6 */
    {MDR_PORTF, PORT_Pin_7,  NONE, NONE},  /* PF7 */
    {MDR_PORTF, PORT_Pin_8,  NONE, NONE},  /* PF8 */
    {MDR_PORTF, PORT_Pin_9,  NONE, NONE},  /* PF9 */
    {MDR_PORTF, PORT_Pin_10, NONE, NONE},  /* PF10 */
    {MDR_PORTF, PORT_Pin_11, NONE, NONE},  /* PF11 */
    {MDR_PORTF, PORT_Pin_12, NONE, NONE},  /* PF12 */
    {MDR_PORTF, PORT_Pin_13, NONE, NONE},  /* PF13 */
    {MDR_PORTF, PORT_Pin_14, NONE, NONE},  /* PF14 */
    {MDR_PORTF, PORT_Pin_15, NONE, NONE}   /* PF15 */
}; 
		