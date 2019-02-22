/*
 * @file   eserial.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#ifndef ESERIAL_H
#define ESERIAL_H

#include "etypes.h"
#include "eprint.h"
#include "estream.h"
#include "epio.h"

#ifdef __cplusplus
extern "C" {
#endif
  
#define ESERIAL_DATA_SIZE 64 
  
#ifdef __cplusplus
}
#endif


// class ESerial: public Stream {
class ESerial {
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

  ESerial(int uart, Pin tx, Pin rx);
  void begin();
  void begin(uint32 baudrate);
  void end();
  void setBaudRate(int baudrate);
  int baudrate() const;
  void setDataBits (DataBits dataBits);
  void setParity (Parity patity);
  void setEvent (Event event);
  void setStopBits (StopBits stopBits);
  DataBits dataBits() const;
  Parity parity() const;
  StopBits stopBits() const;
  virtual int available(void);
  virtual int peek(void);
  virtual byte read(void);
  int availableForWrite(void);
  virtual void flush(void);
  virtual void write(byte);
  // using Print::write;
  void attachInterrupt(Event event, func_ptr handler);
  void detachInterrupt(Event event);
    
private:
  int _serialId;
  void *_serial_ptr;
  int _irq;
  Pin _txPin;
  Pin _rxPin;
  uint32 _baudRate;
  DataBits _dataBits;
  Parity _parity;
  StopBits _stopBits;
  int dataRwCnt;
  int dataTxCnt;
  int dataTxSize;
  int dataRxSize;
  #pragma pack(push,1)
  byte dataRx[ESERIAL_DATA_SIZE];
  byte dataTx[ESERIAL_DATA_SIZE];
  #pragma pack(pop)
};

#endif // ESERIAL_H

