/*
 * @file   EButton.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Button helper file. Based on millis()/micros()
 */

#include "EButton.h"
#include <ecore.h>

EButton::EButton(Pin pin, Type type) {
  _pin = pin;
  _lastState = false;
  _release = _press = false;
  _event = null;
  setType(type);
  _debounce = 60;
}

void EButton::setType(Type type) {
  _type = type;
  pinMode(_pin, _type ? INPUT: INPUT);
}

void EButton::update() {
  bool state = EButton::state();
  if (state != _lastState) {
    _timer = millis();
  } else if (millis() - _timer > _debounce) {
    if (state && !_press)
      _press = true;
    else if (!state && !_release && _press)
      _release = true;
    if (!_click && _release && _press) _click = true;
    if (_event != null) _event();
  }
  _lastState = state;
}

bool EButton::isPress() {
  bool press = _press;
  _press = false;
  return press;
}

bool EButton::isRelease() {
  bool release = _release;
  _release = false;
  return release;
}

bool EButton::isClick() {
  bool click = _click;
  _click = false;
  return click;
}


