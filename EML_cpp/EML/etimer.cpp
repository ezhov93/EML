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

#if defined (USE_MDR1986VE1T) || defined (USE_MDR1986VE3)
#define SIZE 4
#else
#define SIZE 3
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined (USE_MDR1986VE1T) || defined (USE_MDR1986VE3)
static const int irq[SIZE] = {Timer1_IRQn, Timer2_IRQn, Timer3_IRQn , Timer4_IRQn};
#else
static const int irq[SIZE] = {Timer1_IRQn, Timer2_IRQn, Timer3_IRQn};
#endif

static func_ptr handlers_ptr[SIZE] = {};
static bool singleShots[SIZE] = {};

#ifdef __cplusplus
}
#endif

ETimer::ETimer(int timerId, Type type): _timerId(timerId), _type(type) {
  switch (_timerId) {
    case 1: {
      _timer_ptr = MDR_TIMER1;
      _irq = Timer1_IRQn;
    }
    break;
    case 2: {
      _timer_ptr = MDR_TIMER2;
      _irq = Timer2_IRQn;
    }
    break;
    case 3: {
      _timer_ptr = MDR_TIMER3;
      _irq = Timer3_IRQn;
    }
    break;
    #if defined (USE_MDR1986VE1T) || defined (USE_MDR1986VE3)
    case 4: {
    _timer_ptr = MDR_TIMER4;
    _irq = Timer4_IRQn;
    }
    break;
    #endif
    default:
      _timer_ptr = nullptr;
      return;
  }
  MDR_TIMER_TypeDef *timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  RST_CLK_PCLKcmd(PCLK_BIT(_timer_ptr) ,ENABLE);
  TIMER_DeInit(timer);
  
  _interval_ptr = &timer->ARR;
  *_interval_ptr = 1000;
  _singleShot = false;
  _div = TIMER_HCLKdiv8;
  _rate = 1;
  /* pow(2,div) */
  for(int rate=0; rate<_div; ++rate)
    _rate*=2;
  
}

inline int ETimer::interval() const {
  return *_interval_ptr;
}

bool ETimer::isActive() const {
  MDR_TIMER_TypeDef *timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  return timer->CNTRL&TIMER_CNTRL_CNT_EN;
}
 
inline bool ETimer::isSingleShot() const {
  return _singleShot;
}

void ETimer::setSingleShot(bool singleShot) {
  _singleShot = singleShots[_timerId-1] = singleShot;
}

void ETimer::setInterval(int time) {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  *_interval_ptr = time;
  TIMER_SetCounter(timer, 0);
  TIMER_SetCntAutoreload(timer, time);
}

void ETimer::start() {
  start(*_interval_ptr);
}

void ETimer::start(int time) {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  
  TIMER_CntInitTypeDef timerInit;
  
  *_interval_ptr = time;
  
  timerInit.TIMER_Prescaler                = SystemCoreClock/(_type*_rate)-1;
  timerInit.TIMER_Period                   = *_interval_ptr;
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
  TIMER_SetCounter(timer, 0);
  TIMER_BRGInit(timer,_div); 
  
  TIMER_Cmd(timer, ENABLE);
}

inline void ETimer::pause(void) {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  TIMER_Cmd(timer, DISABLE);
}

inline void ETimer::resume(void) {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  TIMER_Cmd(timer, ENABLE);
}

int ETimer::remaningTime() const{
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  return *_interval_ptr - timer->CNT;
}
// void attachInterrupt(int channel, func_ptr handler);
// void detachInterrupt(int channel); 
void ETimer::attachInterrupt(func_ptr handler) {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  _handler = handler;
  handlers_ptr[_timerId-1] = handler;
  TIMER_ClearITPendingBit(timer, 0xFFFF);
  TIMER_ClearFlag(timer, 0xFFFF);
  TIMER_ITConfig(timer, TIMER_STATUS_CNT_ARR, ENABLE);
  NVIC_EnableIRQ((IRQn_Type)_irq);
}
    
void ETimer::detachInterrupt() {
  MDR_TIMER_TypeDef* timer = (MDR_TIMER_TypeDef*)_timer_ptr;
  handlers_ptr[_timerId-1] = null;
  TIMER_ITConfig(timer, TIMER_STATUS_CNT_ARR, DISABLE);
  NVIC_DisableIRQ((IRQn_Type)_irq);
}

#ifdef __cplusplus
extern "C" {
#endif

static void Handler(MDR_TIMER_TypeDef* base, int id) {
  NVIC_DisableIRQ((IRQn_Type)irq[id-1]);
  TIMER_ClearITPendingBit(base, TIMER_STATUS_CNT_ARR);
  TIMER_ClearFlag(base, TIMER_STATUS_CNT_ARR);
  if (handlers_ptr[id-1]!= null) {
    handlers_ptr[id-1]();
    if (singleShots[id -1])
        TIMER_Cmd(base, DISABLE); 
  }
  NVIC_EnableIRQ((IRQn_Type)irq[id-1]);
}
  
void Timer1_IRQHandler() {
  Handler(MDR_TIMER1,1);
}

void Timer2_IRQHandler() {
  Handler(MDR_TIMER2,2);
}

void Timer3_IRQHandler() {
  Handler(MDR_TIMER3,3); 
}
#if defined (USE_MDR1986VE1T) || defined (USE_MDR1986VE3)
void Timer4_IRQHandler() {
  Handler(MDR_TIMER4,4);
}
#endif

#ifdef __cplusplus
}
#endif


