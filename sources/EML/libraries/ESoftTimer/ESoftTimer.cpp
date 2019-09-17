/*
 * @file   ESoftTimer.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Soft timer source file. Based on millis()/micros()
 */
 
#include "ESoftTimer.h"

ESoftTimer::ESoftTimer(uint32 interval, Type type) {
  _type = type;
  if (_type == MS)
    time = millis;
  else 
    time = micros;
  _interval = interval;
  _timer = time();
  _isActive = false;
  _singleShot = false;
  _handler = null;
}

ESoftTimer::Type ESoftTimer::type() const {
  return _type;
}

void ESoftTimer::setType(Type type) {
  _type = type;
}

int ESoftTimer::interval() const {
  return _interval;
}

bool ESoftTimer::isActive() const {
  return _isActive;
}
 
bool ESoftTimer::isSingleShot() const {
  return _singleShot;
}

bool ESoftTimer::isReady() {
  bool temp = _isReady;
  _isReady = false;
  return temp;
}

void ESoftTimer::setSingleShot(bool singleShot) {
  _singleShot = true;
}

void ESoftTimer::setInterval(int interval) {
  _interval = interval;
}

void ESoftTimer::start() {
  start(_interval);
}

void ESoftTimer::start(int interval) {
  _isActive = true;
  _timer = time();
}

void ESoftTimer::pause() {
  _isActive = false;  
}

void ESoftTimer::resume() {
  _isActive = false;
}

void ESoftTimer::reset() {
  _timer = time();
  _isReady = false;
}

void ESoftTimer::update() {
  if (!_isActive)
    return;
  else  {
    if (time() - _timer >= _interval) {
      _isReady = true;
      _timer = time();
      if (_singleShot)
        _isActive = false;
      if (_handler)
        _handler();
    }
  }
}

int ESoftTimer::remaningTime() const {
  return (time() - _timer)-_interval;
}

void ESoftTimer::attachEvent(func_ptr handler) {
  _handler = handler;
}

void ESoftTimer::detachEvent() {
  _handler = null;
}


