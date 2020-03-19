/*
 * @file   ELed.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Led helper class.
 */

#ifndef ELED_H
#define ELED_H

#include "epio.h"

class ELed {
 private:
  Pin _pin;

 public:
  ELed(Pin pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
  }
  void enable(const bool enable = true) { digitalWrite(_pin, enable); }
  void disable(const bool disable = true) { enable(!disable); }
  void toggle() { togglePin(_pin); }
  bool isEnable() const { return digitalRead(_pin); }
  bool isDisable() const { return !isEnable(); }
};

#endif  // ELED_H
