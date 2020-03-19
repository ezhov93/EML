/*
 * @file   EButton.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Button helper class. Based on millis()/micros()
 */

#ifndef EBUTTON_H
#define EBUTTON_H

#include "ecore.h"
#include "epio.h"

class EButton {
 public:
  enum Type { PullUp, PullDown };

 private:
  Pin _pin;
  Type _type;
  uint32 _debounce;
  bool _state;
  bool _release;
  bool _press;
  bool _clicks;
  bool _lastState;
  uint32 _timer;
  func_ptr _event;

 public:
  EButton(Pin, Type = PullDown);

  void setDebounce(int debounce) { _debounce = debounce; }
  void setType(Type type);
  void update();
  bool isPress();
  bool isRelease();
  int clicks();
  bool state() const { return digitalRead(_pin) ^ _type; }
  void attachEvent(func_ptr function) { _event = function; }
  void detachEvent() { _event = null; }
};

#endif  // EBUTTON_H
