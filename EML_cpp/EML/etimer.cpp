/*
 * @file   etimer.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timer file.
 */
 
#include "etimer.h"
#include "einterrupts.h" // for noInterrupts(), interrupts()
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

ETimer::ETimer(uint8 timerId): timerId(timerId) {
  switch (timerId) {
    case 1: {
      timer_ptr = MDR_TIMER1;
      RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1 ,ENABLE);
    }
    break;
    case 2: {
      timer_ptr = MDR_TIMER2;
      RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2 ,ENABLE);
    }
    break;
    case 3: {
      timer_ptr = MDR_TIMER3;
      RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER3 ,ENABLE);
    }
    break;
    default:
      timer_ptr = nullptr;
      return;
    break;
  }
  
  MDR_TIMER_TypeDef* timer = timer_ptr;
  
  TIMER_CntInitTypeDef timerInit;
  
  timerInit.TIMER_Prescaler                = 0x0;
  timerInit.TIMER_Period                   = 0xFFF;
  timerInit.TIMER_CounterMode              = TIMER_CntMode_ClkFixedDir;
  timerInit.TIMER_CounterDirection         = TIMER_CntDir_Up;
  timerInit.TIMER_EventSource              = TIMER_EvSrc_None;
  timerInit.TIMER_FilterSampling           = TIMER_FDTS_TIMER_CLK_div_1;
  timerInit.TIMER_ARR_UpdateMode           = TIMER_ARR_Update_Immediately;
  timerInit.TIMER_ETR_FilterConf           = TIMER_Filter_1FF_at_TIMER_CLK;
  timerInit.TIMER_ETR_Prescaler            = TIMER_ETR_Prescaler_None;
  timerInit.TIMER_ETR_Polarity             = TIMER_ETRPolarity_NonInverted;
  timerInit.TIMER_BRK_Polarity             = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (timer,&timerInit);
  TIMER_BRGInit(timer,TIMER_HCLKdiv1);  
}

int ETimer::interval() const {
  
}

bool ETimer::isActive() const {
    
}
 
bool ETimer::isSingleShot() const {
  
}

void ETimer::setInterval(int msec) {
      
}

void ETimer::start() {

}

void ETimer::start(int msec) {

}

void ETimer::pause(void) {

}

void ETimer::resume(void) {

}

void ETimer::reset() {

}

int ETimer::remaningTime() {
      
}
// void attachInterrupt(int channel, func_ptr handler);
// void detachInterrupt(int channel); 
void ETimer::attachInterrupt(func_ptr handler) {
      
}
    
void ETimer::detachInterrupt() {
     
}

