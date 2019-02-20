/*
 * @file   etimer.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Timer file.
 */
 
#include "etimer.h"
#include "einterrupts.h" // for noInterrupts(), interrupts()

ETimer::ETimer(uint8 number) {
    rcc_clk_id timerID = (rcc_clk_id)(RCC_TIMER1 + (timerNum - 1));
    this->dev = NULL;
    noInterrupts(); // Hack to ensure we're the only ones using
                    // set_this_dev() and friends. TODO: use a lock.
    this_id = timerID;
    this_devp = &this->dev;
    timer_foreach(set_this_dev);
    interrupts();
    ASSERT(this->dev != NULL);
}

void ETimer::pause(void) {
    timer_pause(this->dev);
}

void ETimer::resume(void) {
    timer_resume(this->dev);
}

uint32 ETimer::getPrescaleFactor(void) {
    return timer_get_prescaler(this->dev) + 1;
}

void ETimer::setPrescaleFactor(uint32 factor) {
    timer_set_prescaler(this->dev, (uint16)(factor - 1));
}

uint16 ETimer::getOverflow() {
    return timer_get_reload(this->dev);
}

void ETimer::setOverflow(uint16 val) {
    timer_set_reload(this->dev, val);
}

uint16 ETimer::getCount(void) {
    return timer_get_count(this->dev);
}

void ETimer::setCount(uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_count(this->dev, min(val, ovf));
}

#define MAX_RELOAD ((1 << 16) - 1)
uint16 ETimer::setPeriod(uint32 microseconds) {
    // Not the best way to handle this edge case?
    if (!microseconds) {
        this->setPrescaleFactor(1);
        this->setOverflow(1);
        return this->getOverflow();
    }

    uint32 period_cyc = microseconds * CYCLES_PER_MICROSECOND;
    uint16 prescaler = (uint16)(period_cyc / MAX_RELOAD + 1);
    uint16 overflow = (uint16)((period_cyc + (prescaler / 2)) / prescaler);
    this->setPrescaleFactor(prescaler);
    this->setOverflow(overflow);
    return overflow;
}

void ETimer::setMode(int channel, timer_mode mode) {
    timer_set_mode(this->dev, (uint8)channel, (timer_mode)mode);
}

uint16 ETimer::getCompare(int channel) {
    return timer_get_compare(this->dev, (uint8)channel);
}

void ETimer::setCompare(int channel, uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_compare(this->dev, (uint8)channel, min(val, ovf));
}

void ETimer::attachInterrupt(int channel, voidFuncPtr handler) {
    timer_attach_interrupt(this->dev, (uint8)channel, handler);
}

void ETimer::detachInterrupt(int channel) {
    timer_detach_interrupt(this->dev, (uint8)channel);
}

void ETimer::enableDMA(int channel) {
    timer_dma_enable_req(this->dev, (uint8)channel);
}

void ETimer::disableDMA(int channel) {
    timer_dma_disable_req(this->dev, (uint8)channel);
}

void ETimer::refresh(void) {
    timer_generate_update(this->dev);
}

void ETimer::setMasterModeTrGo(uint32_t mode) {
	this->dev->regs.bas->CR2 &= ~TIMER_CR2_MMS;
	this->dev->regs.bas->CR2 |= mode;
}
