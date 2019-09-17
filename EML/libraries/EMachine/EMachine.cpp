/*
 * @file   EMachine.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  State machine source file. Based on millis()/micros()
 */

#include "EMachine.h"

EMachine::EMachine() { _current = 0; }

EMachine::~EMachine() {}

EMachine::State EMachine::addState(Slot slot) {
  int number = _states.size();
  StatePrivate state;
  state.number = number;
  state.slot = slot;
  _states.append(state);
  return number;
}

void EMachine::addTransition(State state, State nextState, Signal signal) {
  _states[state].nextState.append(_states[nextState].number);
  _states[state].signals.append(signal);
}

void EMachine::begin(State state) { _current = state; }

EMachine::State EMachine::state() { return _current; }

void EMachine::update() {
  if (_states.size() > 0) {
    StatePrivate *current = &_states[_current];
    current->slot();
    const int numberOfTransitions = current->signals.size();
    for (int i = 0; i < numberOfTransitions; ++i) {
      if (current->signals.at(i) != null) {
        if (current->signals.at(i)()) _current = current->nextState.at(i);
      } else
        _current = current->nextState.at(i);
    }
  }
}
