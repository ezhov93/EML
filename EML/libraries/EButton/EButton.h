/*
 * @file   EButton.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Button helper class. Based on millis()/micros()
 */

#ifndef EBUTTON_H
#define EBUTTON_H

#include "ecore.h"

class EButton {
 public:
  enum Type { PullUp, PullDown };

 private:
  Pin _pin;
  Type _type;
  int _debounce;
  bool _release;
  bool _press;
  bool _click;
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
  bool isClick();
  bool state() const { return digitalRead(_pin) ^ _type; }
  void attachEvent(func_ptr function) { _event = function; }
  void detachEvent() { _event = null; }
};

#endif  // EBUTTON_H
