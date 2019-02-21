/*
 * @file   eserial.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#include "eserial.h"

ESerial::ESerial(usart_dev *usart_device,
                               uint8 tx_pin,
                               uint8 rx_pin) {
    this->usart_device = usart_device;
    this->tx_pin = tx_pin;
    this->rx_pin = rx_pin;
}

void ESerial::begin(uint32 baud) {
	begin(baud,SERIAL_8N1);
}
/*
 * Roger Clark.
 * Note. The config parameter is not currently used. This is a work in progress.  
 * Code needs to be written to set the config of the hardware serial control register in question.
 *
*/

void ESerial::begin(uint32 baud, uint8_t config) {
    if (baud > this->usart_device->max_baud) {
        return;
    }

    const stm32_pin_info *txi = &PIN_MAP[this->tx_pin];
    const stm32_pin_info *rxi = &PIN_MAP[this->rx_pin];

    disable_timer_if_necessary(txi->timer_device, txi->timer_channel);

    usart_init(this->usart_device);
    usart_config_gpios_async(this->usart_device,
                             rxi->gpio_device, rxi->gpio_bit,
                             txi->gpio_device, txi->gpio_bit,
                             config);
    usart_set_baud_rate(this->usart_device, USART_USE_PCLK, baud);
    usart_enable(this->usart_device);
}

void ESerial::end(void) {
    usart_disable(this->usart_device);
}

/*
 * I/O
 */

int ESerial::read(void) {
	if(usart_data_available(usart_device) > 0) {
		return usart_getc(usart_device);
	} else {
		return -1;
	}
}

int ESerial::available(void) {
    return usart_data_available(this->usart_device);
}

/* Roger Clark. Added function missing from LibMaple code */

int ESerial::peek(void) {
    return usart_peek(this->usart_device);
}

int ESerial::availableForWrite(void) {
    return this->usart_device->wb->size-rb_full_count(this->usart_device->wb);
}

size_t ESerial::write(unsigned char ch) {
  usart_putc(this->usart_device, ch);
	return 1;
}

/* edogaldo: Waits for the transmission of outgoing serial data to complete (Arduino 1.0 api specs) */
void ESerial::flush(void) {
    while(!rb_is_empty(this->usart_device->wb)); // wait for TX buffer empty
    while(!((this->usart_device->regs->SR) & (1<<USART_SR_TC_BIT))); // wait for TC (Transmission Complete) flag set 
}
