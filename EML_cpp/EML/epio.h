/*
 * @file   epio.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Pin I/O interface..
 */

#ifndef EPIO_H
#define EPIO_H

#include "etypes.h"

typedef enum PinState {
    LOW,
    HIGH
} PinState;

typedef enum PinMode {
    OUTPUT, 
    OUTPUT_ANALOG,
    INPUT,
    INPUT_ANALOG,
    INPUT_PULLUP,
    INPUT_PULLDOW,
} PinMode;

typedef enum Pin {
	PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,	
	PA8, PA9, PA10,	PA11, PA12,	PA13, PA14,	PA15,
	PB0, PB1, PB2, PB3,	PB4, PB5, PB6, PB7,	
	PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
	PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
	PC8, PC9, PC10, PC11, PC12, PC13, PC14,	PC15,
	PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,
	PD8, PD9, PD10,	PD11, PD12,	PD13, PD14,	PD15,
	PE0, PE1, PE2, PE3,	PE4, PE5, PE6, PE7,
	PE8, PE9, PE10,	PE11, PE12,	PE13, PE14,	PE15,
	PF0, PFB1, PF2,	PF3, PF4, PF5, PF6,	PF7,
	PF8, PF9, PF10,	PF11, PF12,	PF13, PF14,	PF15
}Pin;

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Number of pin to configure.
 * @param mode Mode corresponding to desired pin behavior.
 * @see WiringPinMode
 */
void pinMode(Pin pin, PinMode mode);

/**
 * Writes a (digital) value to a pin.  The pin must have its
 * mode set to OUTPUT or OUTPUT_OPEN_DRAIN.
 *
 * @param pin Pin to write to.
 * @param value Either LOW (write a 0) or HIGH (write a 1).
 * @see pinMode()
 */
void digitalWrite(Pin pin, uint32 value);

/**
 * Read a digital value from a pin.  The pin must have its mode set to
 * one of INPUT, INPUT_PULLUP, and INPUT_PULLDOWN.
 *
 * @param pin Pin to read from.
 * @return LOW or HIGH.
 * @see pinMode()
 */
uint32 digitalRead(Pin pin);

/**
 * Read an analog value from pin.  This function blocks during ADC
 * conversion, and has 12 bits of resolution.  The pin must have its
 * mode set to INPUT_ANALOG.
 *
 * @param pin Pin to read from.
 * @return Converted voltage, in the range 0--4095, (i.e. a 12-bit ADC
 *         conversion).
 * @see pinMode()
 */
uint16 analogRead(Pin pin);

// void pwmWrite(uint8 pin, uint16 duty_cycle)

uint32 pulseIn( Pin pin,  PinState state, uint32 timeout_ms = 1000000L ) ;

/**
 * Roger Clark. 20140103
 * Added function to replicate the Arduino PWM functionality or range 0 to 255 
 * User code is expected to determine and honor the maximum value
 * (based on the configured period).
 *
 * @param pin PWM output pin
 * @param duty_cycle Duty cycle to set. (Range is 0 to 255)
 */
void analogWrite(Pin pin, uint8 duty8);


void shiftOut(Pin data, Pin clock, uint8 bitOrder, uint8 value);

uint32 shiftIn(Pin data, Pin clock, uint32 bitOrder);

#endif // EPIO_H
