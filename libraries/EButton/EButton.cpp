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
  _clicks = 0;
  _state = false;
}

void EButton::setType(Type type) {
  _type = type;
  pinMode(_pin, _type ? INPUT : INPUT);
}

void EButton::update() {
  bool state = EButton::state();

  if (state != _lastState) {
    _timer = millis();
  }

  if (millis() - _timer > _debounce) {
    if (state != _state) {
      _state = state;
      if (_state)
        _press = true;
      else
        _release = true;
      if (_event != null) _event();
    }
  }

  _lastState = state;
}

bool EButton::isPress() {
  update();
  bool press = _press;
  _press = false;
  return press;
}

bool EButton::isRelease() {
  update();
  bool release = _release;
  _release = false;
  return release;
}

int EButton::clicks() {
  update();
  int tmp = _clicks;
  _clicks = 0;
  return tmp;
}
