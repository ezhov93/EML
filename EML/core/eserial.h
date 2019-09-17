/*
 * @file   eserial.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#ifndef ESERIAL_H
#define ESERIAL_H

#include "estream.h"
#include "epio.h"

class ESerial: public EStream {
public:
  enum DataBits { 
    Data5 = 0x00,
    Data6 = 0x20,
    Data7 = 0x40,
    Data8 = 0x60
  };
  enum Parity { 
    NoParity = 0x00,
    EvenParity = 0x06,
    OddParity = 0x02,
    MarkParity = 0x82,
    SpaceParity = 0x86
  };
  enum StopBits {
    OneStop = 0x00,
    TwoStop = 0x08
  };
  enum Event { TransmittedData, ReceivedData };

  ESerial(int uart, Pin tx, Pin rx, int size=64);
  ~ESerial();
  void begin();
  void begin(uint32 baudrate);
  void end();
  void setBaudRate(uint32 baudrate);
  int baudrate() const;
  void setDataBits (DataBits dataBits);
  void setParity (Parity patity);
  void setStopBits (StopBits stopBits);
  DataBits dataBits() const;
  Parity parity() const;
  StopBits stopBits() const;
  virtual int available(void);
  virtual int peek(void);
  virtual int read(void);
  int availableForWrite(void);
  virtual void flush(void);
  virtual size_t write(byte ch);
  virtual size_t write(const void *buf, uint32 len);
  inline size_t write(unsigned long n) { return write((byte)n); }
  inline size_t write(long n) { return write((byte)n); }
  inline size_t write(unsigned int n) { return write((byte)n); }
  inline size_t write(int n) { return write((byte)n); }
  using EPrint::write;
  void attachInterrupt(Event event, func_ptr handler);
  void detachInterrupt(Event event);
    
private:
  int _serialId;
  void *_serial_ptr;
  int _irq;
  uint32 _baudRate;
  DataBits _dataBits;
  Parity _parity;
  StopBits _stopBits;
  struct {
    int size;
    Pin pin;
    byte *data;
    byte *ring;
  } _rx, _tx;
  
};

#endif // ESERIAL_H

