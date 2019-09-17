/*
 * @file   epio.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Digital I/O implementation
 */

#include "epio.h"
#include "ebits.h"
#include "epio_private.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_dac.h"

static bool useAdc = false;
static bool useDac1 = false;
static bool useDac2 = false;

static inline void setupAdc(Pin pin) {
	if (!useAdc) {
		RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);
		ADC_InitTypeDef adc;
		ADCx_InitTypeDef adcX;
		ADC_DeInit();
		ADC_StructInit(&adc);
		ADC_Init (&adc);
		ADCx_StructInit (&adcX);
		
		adcX.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
		adcX.ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;
		adcX.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
		adcX.ADC_ChannelNumber    = pinMap[pin].chAdc;
		adcX.ADC_Channels         = 0;
		adcX.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;
		adcX.ADC_LowLevel         = 0;
		adcX.ADC_HighLevel        = 0;
		adcX.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
		adcX.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
		adcX.ADC_Prescaler        = ADC_CLK_div_16;
		adcX.ADC_DelayGo          = 0x7;
		ADC1_Init (&adcX);
		
		ADC1_Cmd(ENABLE);
		useAdc = true;
	}
}

static inline void setupDac(Pin pin) {
	if (!useDac1 && pinMap[pin].chDac==1) {
		RST_CLK_PCLKcmd(RST_CLK_PCLK_DAC, ENABLE);
		DAC1_Init(DAC1_AVCC);
		DAC1_Cmd(ENABLE);
		useDac1 = true;
	}
	else if (!useDac2 && pinMap[pin].chDac==2) {
		RST_CLK_PCLKcmd(RST_CLK_PCLK_DAC, ENABLE);
		DAC2_Init(DAC2_AVCC);
		DAC2_Cmd(ENABLE);
		useDac2 = true;
	}
}

void pinMode(Pin pin, PinMode mode) {
	PORT_InitTypeDef conf;
	PORT_StructInit(&conf);
	RST_CLK_PCLKcmd(pinMap[pin].rstClk, ENABLE);
	conf.PORT_Pin = pinMap[pin].pin;
		
	switch (mode) {
		case OUTPUT: {
			conf.PORT_MODE = PORT_MODE_DIGITAL;
			conf.PORT_OE = PORT_OE_OUT;
		}
		break ;
		case OUTPUT_ANALOG: {
      setupDac(pin);
      conf.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
			conf.PORT_OE = PORT_OE_OUT;
			conf.PORT_MODE = PORT_MODE_ANALOG;
		}
		break;
		case INPUT: {
			conf.PORT_OE = PORT_OE_IN;
			conf.PORT_MODE = PORT_MODE_DIGITAL;
		}
		break;
		case INPUT_ANALOG: {
			setupAdc(pin);
      conf.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
			conf.PORT_OE = PORT_OE_IN;
			conf.PORT_MODE = PORT_MODE_ANALOG;
		}
		break;
		case INPUT_PULLUP: {
			conf.PORT_PULL_UP = PORT_PULL_UP_ON;
  		conf.PORT_OE = PORT_OE_IN;
	  	conf.PORT_MODE = PORT_MODE_DIGITAL;
		}
		break;
		case INPUT_PULLDOW: {
			conf.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
  		conf.PORT_OE = PORT_OE_IN;
			conf.PORT_MODE = PORT_MODE_DIGITAL;
		}
		break;
	}
	conf.PORT_SPEED = PORT_SPEED_MAXFAST;
	conf.PORT_FUNC = PORT_FUNC_PORT;
	
	PORT_Init(pinMap[pin].port, &conf);	
}

inline uint32 digitalRead(Pin pin) {
    return (uint32)PORT_ReadInputDataBit(pinMap[pin].port, pinMap[pin].pin);
}

inline void digitalWrite(Pin pin, int val) {
    PORT_WriteBit(pinMap[pin].port, pinMap[pin].pin, (BitAction)val);
}

void togglePin(Pin pin) {
	uint32 state = PORT_ReadInputDataBit(pinMap[pin].port, pinMap[pin].pin);
	PORT_WriteBit(pinMap[pin].port, pinMap[pin].pin, state?Bit_RESET:Bit_SET);
}

uint16 analogRead(Pin pin) {
	uint32 ch = pinMap[pin].chAdc;
	ADC1_SetChannel(ch);
  ADC1_Start();
  while(!ADC_GetFlagStatus(ADC1_FLAG_END_OF_CONVERSION)){};
                               	return ADC1_GetResult();
}

void analogWrite(Pin pin, int val)
{
	if (pinMap[pin].chDac==1)
		DAC1_SetData(val);
	else if (pinMap[pin].chDac==2)
		DAC2_SetData(val);
}

void analogReference(AnalogReference analogReference) {
  switch (analogReference) {
    case ADC_DEFAULT:
    case ADC_INTERNAL:
      bitClear(MDR_ADC->ADC1_CFG, 11);
    break;
    case DAC_DEFAULT:
    case DAC_INTERNAL:
      bitClear(MDR_DAC->CFG, 0);
      bitClear(MDR_DAC->CFG, 1);
    break;
    case DAC_EXTERNAL:
      bitSet(MDR_DAC->CFG, 0);
      bitSet(MDR_DAC->CFG, 1);
    break;
    case ADC_EXTERNAL:
      bitSet(MDR_ADC->ADC1_CFG, 11);
    
    break;
  }
}

void shiftOut(Pin dataPin, Pin clockPin, int bitOrder, int value) {
    digitalWrite(clockPin, LOW);
    for (int i = 0; i < 8; i++) {
        int bit = bitOrder == LSBFIRST ? i : (7 - i);
        digitalWrite(dataPin, (value >> bit) & 0x1);
		togglePin(clockPin);
		togglePin(clockPin);
    }
}

uint32_t shiftIn(Pin dataPin, Pin clockPin, int bitOrder )
{
  uint8_t value = 0;
  for (int i=0 ; i < 8 ; ++i)  {
    digitalWrite(clockPin, HIGH) ;
    if ( bitOrder == LSBFIRST) 
      value |= digitalRead(dataPin) << i;
    else
      value |= digitalRead(dataPin) << (7 - i);
    digitalWrite(clockPin, LOW) ;
  }
  return value ;
}


