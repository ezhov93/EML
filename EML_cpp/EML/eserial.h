/*
 * @file   eserial.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#ifndef ESERIAL_H
#define ESERIAL_H

#include "eprint.h"
#include "estream.h"

#if !(defined(SERIAL_TX_BUFFER_SIZE) && defined(SERIAL_RX_BUFFER_SIZE))
#if (RAMEND < 1000)
#define SERIAL_TX_BUFFER_SIZE 16
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif
 
struct usart_dev;

#define SERIAL_8N1	0B00000000
#define SERIAL_8N2	0B00100000
#define SERIAL_9N1	0B00001000
#define SERIAL_9N2	0B00101000	

#define SERIAL_8E1	0B00001010
#define SERIAL_8E2	0B00101010
/* not supported:
#define SERIAL_9E1	0B00001010
#define SERIAL_9E2	0B00101010
*/
#define SERIAL_8O1	0B00001011
#define SERIAL_8O2	0B00101011
/* not supported:
#define SERIAL_9O1	0B00001011
#define SERIAL_9O2	0B00101011
*/

class ESerial: public Stream {

public:
    ESerial(struct usart_dev *usart_device,
                   uint8 tx_pin,
                   uint8 rx_pin);

    void begin(uint32 baud);
    void begin(uint32 baud,uint8_t config);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

    int txPin(void) { return this->tx_pin; }
    int rxPin(void) { return this->rx_pin; }
	
	operator bool() { return true; }

    struct usart_dev* c_dev(void) { return this->usart_device; }
private:
    struct usart_dev *usart_device;
    uint8 tx_pin;
    uint8 rx_pin;
};

