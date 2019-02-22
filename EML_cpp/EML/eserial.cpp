/*
 * @file   eserial.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Serial port implementation.
 */

#include "eserial.h"
#include "MDR32F9Qx_uart.h"     
#include "MDR32F9Qx_rst_clk.h"  
#include "MDR32F9Qx_port.h"     
#include "epio_private.h"


#ifdef __cplusplus
extern "C" {
#endif
#define NUMBER_OF_UART 2
  
#define FIFO_SIZE UART_IT_FIFO_LVL_12words
  
static func_ptr recvHandler_ptr[NUMBER_OF_UART] = {};
static func_ptr trmHandler_ptr[NUMBER_OF_UART] = {};
static func_ptr toHandler_ptr[NUMBER_OF_UART] = {};
static const int irq[] = {UART1_IRQn,UART2_IRQn};
    
#undef NUMBER_OF_UART
#ifdef __cplusplus
}
#endif

ESerial::ESerial(int uart, Pin tx, Pin rx)  {
  switch (_serialId = uart) {
    case 1: {
      _serial_ptr = MDR_UART1;
      RST_CLK_PCLKcmd(RST_CLK_PCLK_UART1, ENABLE);
    }
    break;
    case 2: {
      _serial_ptr = MDR_UART2;
      RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);
    }
    break;
    default:
      return;
  }
  
  _txPin = tx;
  _rxPin = rx;
  
  _baudRate = 9600;
  _dataBits = Data8;
  _stopBits = OneStop;
  _parity = NoParity;
  
  /*memset(dataRx,0, sizeof (dataRx));
  memset(dataTx,0, sizeof (dataTx));*/

  PORT_InitTypeDef port;
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
 
  PORT_StructInit(&port);
  
  RST_CLK_PCLKcmd(pinMap[_txPin].rstClk,ENABLE);
  RST_CLK_PCLKcmd(pinMap[_rxPin].rstClk,ENABLE);
  
  port.PORT_FUNC = PORT_FUNC_OVERRID;
  port.PORT_SPEED = PORT_SPEED_MAXFAST;
  port.PORT_MODE = PORT_MODE_DIGITAL;

  port.PORT_OE = PORT_OE_OUT;
  port.PORT_Pin = pinMap[_txPin].pin;
  PORT_Init(pinMap[_txPin].port, &port);

  port.PORT_OE = PORT_OE_IN;
  port.PORT_Pin = pinMap[_rxPin].pin;
  PORT_Init(pinMap[_rxPin].port, &port);
    
  UART_BRGInit(serial, UART_HCLKdiv1);
  
  UART_DMAConfig (serial, FIFO_SIZE, FIFO_SIZE);
  UART_DMACmd(serial, UART_DMA_TXE | UART_DMA_RXE, ENABLE);
}

void ESerial::begin() {
	begin(_baudRate);
}

void ESerial::begin(uint32 baudrate) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  UART_DeInit(serial);
  UART_InitTypeDef conf;
  conf.UART_BaudRate = _baudRate;
  conf.UART_WordLength = _dataBits;
  conf.UART_StopBits = _stopBits;
  conf.UART_Parity = _parity;
  
  conf.UART_FIFOMode = UART_FIFO_OFF;
  conf.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | 
                                  UART_HardwareFlowControl_TXE;
  UART_Init (serial,&conf);
  UART_Cmd(serial,ENABLE);
}

void ESerial::end(void) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  UART_Cmd(serial,DISABLE);
}

inline void ESerial::setBaudRate(int baudrate) {
    _baudRate = baudrate;
}

inline int ESerial::baudrate() const {
  return _baudRate;
}

inline void ESerial::setDataBits (DataBits dataBits) {
  _dataBits = dataBits;
}

inline void ESerial::setParity (Parity parity) {
  _parity = parity;
}

inline void ESerial::setEvent (Event event) {
  
}

inline void ESerial::setStopBits (StopBits stopBits) {
  _stopBits = stopBits;
}

inline ESerial::DataBits ESerial::dataBits() const {
  return _dataBits;
}

inline ESerial::Parity ESerial::parity() const {
  return _parity;
}

inline ESerial::StopBits ESerial::stopBits() const {
  return _stopBits;
}

byte ESerial::read(void) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
  if (UART_GetFlagStatus(serial, UART_FLAG_RXFE) == RESET)  
		return UART_ReceiveData(MDR_UART2)&0xFF;
  else
    return 0;
}

int ESerial::available(void) {
    return 0;
}

int ESerial::peek(void) {
    return 0;
}

int ESerial::availableForWrite(void) {
    return 0;
}

void ESerial::write(byte ch) {
  MDR_UART_TypeDef *serial = (MDR_UART_TypeDef*)_serial_ptr;
	memcpy(uart2Tx, data, size);
	 = size;
	int numberOfByte = size<FIFO_TX_SIZE? size : FIFO_TX_SIZE;
	for (uart2TxCnt = 0; uart2TxCnt < numberOfByte; uart2TxCnt++)
		UART2->DR = uart2Tx[uart2TxCnt];
}

void ESerial::flush(void) {
    /*while(!rb_is_empty(this->usart_device->wb)); // wait for TX buffer empty
    while(!((this->usart_device->regs->SR) & (1<<USART_SR_TC_BIT))); // wait for TC (Transmission Complete) flag set
*/  
}

void ESerial::attachInterrupt(Event event, func_ptr handler) {
  
}

void ESerial::detachInterrupt(Event event) {
  
}

#ifdef __cplusplus
extern "C" {
#endif


void UART2_Handler()
{	
	uint8_t cnt;
	uint16_t statusIrg = UART2->MIS;
	
	NVIC_DisableIRQ(UART2_IRQn);
	
	if (statusIrg & (1 << 5)){	// Tx
		UART2->ICR |= 1<<5;
		uint16_t lenght = uart2TxSize - uart2TxCnt;
		
		if(lenght) {
			if (lenght > FIFO_TX_SIZE)
				lenght = FIFO_TX_SIZE;
			for (cnt=0; cnt<lenght; ++cnt)
				UART2->DR = uart2Tx[uart2TxCnt++];
		}
		else 
			uart2TxCnt = 0; 
	}
	
	if (statusIrg & (1 << 4)){	//Rx
		UART2->ICR |= 1<<4;		
		while (!UART2_FIFO_RXE)
			uart2Rx[uart2RxCnt++] = UART2->DR;
	}
	
	if (statusIrg & (1 << 6)) { // Timeout
		UART2->ICR |= 1<<6;
		while (!UART2_FIFO_RXE) {
			uart2Rx[uart2RxCnt++] = UART2->DR;	
		}
		Uart2_ReadEvent(uart2Rx, uart2RxCnt);
		uart2RxCnt = 0;
	}
	NVIC_EnableIRQ(UART2_IRQn);
}

void Uart2_Write(void *data, uint32_t size) 
{
	memcpy(uart2Tx, data, size);
	uart2TxSize = size;
	int numberOfByte = size<FIFO_TX_SIZE? size : FIFO_TX_SIZE;
	for (uart2TxCnt = 0; uart2TxCnt < numberOfByte; uart2TxCnt++)
		UART2->DR = uart2Tx[uart2TxCnt];
}


static void Handler(MDR_UART_TypeDef* base, int id) {
	NVIC_DisableIRQ((IRQn_Type)irq[id-1]);

  if (UART_GetITStatus(base, UART_IT_TX)) {
		while(!UART_GetFlagStatus(base, UART_FLAG_RXFE)) 
//			data[size++] = UART_ReceiveData(base);
		UART_ClearITPendingBit(base, UART_IT_TX);
	}
  if (UART_GetITStatus(base, UART_IT_RX)) {
		while(!UART_GetFlagStatus(base, UART_FLAG_RXFE)) 
//			data[size++] = UART_ReceiveData(base);
		UART_ClearITPendingBit(base, UART_IT_RX);
	}
	if (UART_GetITStatus(base, UART_IT_RT)) {
		while(!UART_GetFlagStatus(base, UART_FLAG_RXFE))
//			data[size++] = UART_ReceiveData(base);
		// Uart2_ReadEvent(data, size);
		// size = 0;
		UART_ClearITPendingBit(base, UART_IT_RT);
	}
	
	NVIC_EnableIRQ((IRQn_Type)irq[id-1]);
}
  
void UART1_IRQHandler() {
  Handler(MDR_UART1,1);
}

void UART2_IRQHandler() {
  Handler(MDR_UART2,2);
}

#ifdef __cplusplus
}
#endif


