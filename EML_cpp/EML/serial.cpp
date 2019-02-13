/*
 * @file   bit_constans.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Sserial port implementation.
 */


#include "serial.h"

HardwareSerial::HardwareSerial(usart_dev *usart_device,
                               uint8 tx_pin,
                               uint8 rx_pin) {
    this->usart_device = usart_device;
    this->tx_pin = tx_pin;
    this->rx_pin = rx_pin;
}

void HardwareSerial::begin(uint32 baud) 
{
	begin(baud,SERIAL_8N1);
}
/*
 * Roger Clark.
 * Note. The config parameter is not currently used. This is a work in progress.  
 * Code needs to be written to set the config of the hardware serial control register in question.
 *
*/

void HardwareSerial::begin(uint32 baud, uint8_t config) 
{
 //   ASSERT(baud <= this->usart_device->max_baud);// Roger Clark. Assert doesn't do anything useful, we may as well save the space in flash and ram etc

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

void HardwareSerial::end(void) {
    usart_disable(this->usart_device);
}

/*
 * I/O
 */

int HardwareSerial::read(void) {
	if(usart_data_available(usart_device) > 0) {
		return usart_getc(usart_device);
	} else {
		return -1;
	}
}

int HardwareSerial::available(void) {
    return usart_data_available(this->usart_device);
}

/* Roger Clark. Added function missing from LibMaple code */

int HardwareSerial::peek(void)
{
    return usart_peek(this->usart_device);
}

int HardwareSerial::availableForWrite(void)
{
    return this->usart_device->wb->size-rb_full_count(this->usart_device->wb);
}

size_t HardwareSerial::write(unsigned char ch) {

    usart_putc(this->usart_device, ch);
	return 1;
}

/* edogaldo: Waits for the transmission of outgoing serial data to complete (Arduino 1.0 api specs) */
void HardwareSerial::flush(void) {
    while(!rb_is_empty(this->usart_device->wb)); // wait for TX buffer empty
    while(!((this->usart_device->regs->SR) & (1<<USART_SR_TC_BIT))); // wait for TC (Transmission Complete) flag set 
}
