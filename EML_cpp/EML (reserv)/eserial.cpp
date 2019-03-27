/*
 * @file   eserial.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#include "eserial.h"
#include "MDR32F9Qx_uart.h"     
#include "MDR32F9Qx_rst_clk.h"  
#include "MDR32F9Qx_config.h"   
#include "MDR32F9Qx_port.h"     
#include "epio_private.h"
#include "ering_private.h"


#define DMA 1

#if !DMA
#define FIFO_SIZE     1
#else
#define FIFO_RX_SIZE UART_IT_FIFO_LVL_14words
#define FIFO_TX_SIZE UART_IT_FIFO_LVL_2words
#define FIFO_SIZE     16
#endif

#define NUMBER_OF_UART 2

using namespace EPrivate;

#ifdef __cplusplus
extern "C" {
#endif
  
static struct Uart {
  struct { func_ptr recv, trm; } handlers;
  ERingPrivate *ringRx_ptr;
  ERingPrivate *ringTx_ptr;
  int size;
  IRQn_Type irq;
  MDR_UART_TypeDef* base;
} gUart[NUMBER_OF_UART];

#ifdef __cplusplus
}
#endif

static __attribute__(( constructor (101))) void initialize() {
  for (int cnt=0; cnt<NUMBER_OF_UART; ++cnt) {
    gUart[cnt].handlers.recv = NULL;
    gUart[cnt].handlers.trm = NULL;
  }
  gUart[0].base = MDR_UART1;
  gUart[0].irq = UART1_IRQn;
  gUart[1].base = MDR_UART2;
  gUart[1].irq = UART2_IRQn;
}

#undef NUMBER_OF_UART

template <Eml::Size SIZE>
ESerial<SIZE>::ESerial(int uart, Pin tx, Pin rx)  {
  switch (_serialId = uart) {
    case 1: {
      _serial_ptr = MDR_UART1;
      _irq = UART1_IRQn;
    }
    break;
    case 2: {
      _serial_ptr = MDR_UART2;
      _irq = UART2_IRQn;
    }
    break;
    default:
      _serial_ptr = nullptr;
      return;
  }
  
  ERingPrivate *ringRx = (ERingPrivate*)&_rx.ring;  
  ringRx->data = _rx.data;
  ringRx->size = SIZE;
  ERingPrivate::clear(*ringRx);

  ERingPrivate *ringTx = (ERingPrivate*)&_tx.ring;  
  ringTx->data = _tx.data;
  ringTx->size = SIZE;
  ERingPrivate::clear(*ringTx);
  
  gUart[_serialId-1].size = SIZE;
  gUart[_serialId-1].ringRx_ptr = ringRx;
  gUart[_serialId-1].ringTx_ptr = ringTx;
  
  _tx.pin = tx;
  _rx.pin = rx;
  
  _baudRate = 9600;
  _dataBits = Data8;
  _stopBits = OneStop;
  _parity = NoParity;
}

template <Eml::Size SIZE>
void ESerial<SIZE>::begin() {
	begin(_baudRate);
}

template <Eml::Size SIZE>
void ESerial<SIZE>::begin(uint32 baudrate) {
  PORT_InitTypeDef port;
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;

  RST_CLK_PCLKcmd(PCLK_BIT(_serial_ptr), ENABLE);

  PORT_StructInit(&port);
  
  RST_CLK_PCLKcmd(pinMap[_tx.pin].rstClk,ENABLE);
  RST_CLK_PCLKcmd(pinMap[_rx.pin].rstClk,ENABLE);
  
  port.PORT_PULL_UP = PORT_PULL_UP_OFF;
  port.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  port.PORT_PD_SHM = PORT_PD_SHM_OFF;
  port.PORT_PD = PORT_PD_DRIVER;
  port.PORT_GFEN = PORT_GFEN_OFF;
  port.PORT_FUNC = PORT_FUNC_OVERRID;
  port.PORT_SPEED = PORT_SPEED_MAXFAST;
  port.PORT_MODE = PORT_MODE_DIGITAL;

  port.PORT_OE = PORT_OE_OUT;
  port.PORT_Pin = pinMap[_tx.pin].pin;
  PORT_Init(pinMap[_tx.pin].port, &port);

  port.PORT_OE = PORT_OE_IN;
  port.PORT_Pin = pinMap[_rx.pin].pin;
  PORT_Init(pinMap[_rx.pin].port, &port);
  
  UART_BRGInit(serial, UART_HCLKdiv1);

  UART_DeInit(serial);
  UART_InitTypeDef conf;
  conf.UART_BaudRate = _baudRate;
  conf.UART_WordLength = _dataBits;
  conf.UART_StopBits = _stopBits;
  conf.UART_Parity = _parity;
  
  #if DMA
  conf.UART_FIFOMode = UART_FIFO_ON;
  #else
  conf.UART_FIFOMode = UART_FIFO_OFF;
  #endif
  conf.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | 
                                  UART_HardwareFlowControl_TXE;
  UART_Init (serial,&conf);
  
  UART_ITConfig(serial, UART_IT_TX | UART_IT_RX | UART_IT_RT, ENABLE);
  NVIC_EnableIRQ((IRQn_Type)_irq);
   
  #if DMA
  UART_DMAConfig (serial, FIFO_RX_SIZE, FIFO_TX_SIZE);
  UART_DMACmd(serial, UART_DMA_TXE | UART_DMA_RXE, ENABLE);
  #endif
  
  UART_Cmd(serial,ENABLE);
  
}

template <Eml::Size SIZE>
void ESerial<SIZE>::end(void) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  UART_Cmd(serial,DISABLE);
}

template <Eml::Size SIZE>
inline void ESerial<SIZE>::setBaudRate(int baudrate) {
    _baudRate = baudrate;
}

template <Eml::Size SIZE>
inline int ESerial<SIZE>::baudrate() const {
  return _baudRate;
}

template <Eml::Size SIZE>
inline void ESerial<SIZE>::setDataBits (DataBits dataBits) {
  _dataBits = dataBits;
}

template <Eml::Size SIZE>
inline void ESerial<SIZE>::setParity (Parity parity) {
  _parity = parity;
}

template <Eml::Size SIZE>
inline void ESerial<SIZE>::setEvent (Event event) {
  
}

template <Eml::Size SIZE>
inline void ESerial<SIZE>::setStopBits (StopBits stopBits) {
  _stopBits = stopBits;
}

template <Eml::Size SIZE>
inline ESerial<SIZE>::DataBits ESerial<SIZE>::dataBits() const {
  return _dataBits;
}

template <Eml::Size SIZE>
inline ESerial<SIZE>::Parity ESerial<SIZE>::parity() const {
  return _parity;
}

template <Eml::Size SIZE>
inline ESerial<SIZE>::StopBits ESerial<SIZE>::stopBits() const {
  return _stopBits;
}

template <Eml::Size SIZE>
int ESerial<SIZE>::read(void) {
  byte ch;
  ERingPrivate *ringRx = (ERingPrivate*)&_rx.ring;  
  ERingPrivate::pop(*ringRx, &ch, sizeof(ch));
  return ch;
}

template <Eml::Size SIZE>
int ESerial<SIZE>::available(void) {
   ERingPrivate *ringRx = (ERingPrivate*)&_rx.ring;  
   return ERingPrivate::count(*ringRx);
}

template <Eml::Size SIZE>
int ESerial<SIZE>::peek(void) {
  byte ch;
  ERingPrivate *ringRx = (ERingPrivate*)&_rx.ring;  
  ERingPrivate::peek(*ringRx, &ch, sizeof(ch));
  return ch;
}

template <Eml::Size SIZE>
int ESerial<SIZE>::availableForWrite(void) {
   ERingPrivate *ringRx = (ERingPrivate*)&_rx.ring;  
   return ERingPrivate::count(*ringRx);
}

template <Eml::Size SIZE>
size_t ESerial<SIZE>::write(byte ch) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  ERingPrivate *ringTx = (ERingPrivate*)&_tx.ring;  
  ERingPrivate::push(*ringTx, &ch, 1);
  if (availableForWrite()<FIFO_SIZE && 
      !UART_GetFlagStatus(serial, UART_FLAG_TXFF)) {
    ERingPrivate::pop(*ringTx, &ch, 1);
    UART_SendData(serial, ch);
  }
  return 1;
}

template <Eml::Size SIZE>
void ESerial<SIZE>::flush(void) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  ERingPrivate *ringTx = (ERingPrivate*)&_tx.ring;  
  while(!ERingPrivate::isEmpty(*ringTx)); // wait for TX buffer empty
  while(!UART_GetFlagStatus(serial, UART_FLAG_TXFE)); // wait for Transmite*/
}

template <Eml::Size SIZE>
void ESerial<SIZE>::attachInterrupt(Event event, func_ptr handler) {
  switch (event) {
    case TransmittedData: {
     gUart[_serialId-1].handlers.trm = handler;
    }
    break;
    case ReceivedData:{
      gUart[_serialId-1].handlers.recv = handler;
    }
    break;
    default:
      return;
  }
}

template <Eml::Size SIZE>
void ESerial<SIZE>::detachInterrupt(Event event) {
  switch (event) {
    case TransmittedData: {
      gUart[_serialId-1].handlers.trm = NULL;
    }
    break;
    case ReceivedData:{
      gUart[_serialId-1].handlers.recv = NULL;
    }
    break;
    default:
      return;
  }
}

#ifdef __cplusplus
extern "C" {
#endif

bool Write(Uart *uart) {
  byte ch;
  if(!ERingPrivate::pop(*uart->ringTx_ptr, &ch, sizeof(ch)))
    return false;
  UART_SendData(uart->base, ch);
  return true;
}

bool Read(Uart *uart) {
  byte ch = UART_ReceiveData(uart->base);
  ERingPrivate::push(*uart->ringRx_ptr, &ch, sizeof(ch));
  return true;
}
  
static void Handler(Uart *uart) {
	NVIC_DisableIRQ(uart->irq);
  
  if (UART_GetITStatus(uart->base, UART_IT_TX)) {
		while(!UART_GetFlagStatus(uart->base, UART_FLAG_TXFF)) { 
        if (!Write(uart)) {
          if (uart->handlers.trm)
            uart->handlers.trm();
          break;
        }
    }
		UART_ClearITPendingBit(uart->base, UART_IT_TX);
	}
  if (UART_GetITStatus(uart->base, UART_IT_RX)) {
		while(!UART_GetFlagStatus(uart->base, UART_FLAG_RXFE)) 
      Read(uart);
		UART_ClearITPendingBit(uart->base, UART_IT_RX);
	}
	if (UART_GetITStatus(uart->base, UART_IT_RT)) {
		while(!UART_GetFlagStatus(uart->base, UART_FLAG_RXFE))
      Read(uart);
    if (uart->handlers.recv)
      uart->handlers.recv();
		UART_ClearITPendingBit(uart->base, UART_IT_RT);
	}
	
	NVIC_EnableIRQ(uart->irq);
}
  
void UART1_IRQHandler() {
  Handler(&gUart[0]);
}

void UART2_IRQHandler() {
  Handler(&gUart[1]);
}

#ifdef __cplusplus
}
#endif

EML_ADD_TEMPLATE_SIZE(ESerial)


