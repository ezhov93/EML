/*
 * @file   EClaswMachine.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  State machine class. Based on millis()/micros()
 */

#ifndef ECLASSMACHINE_H
#define ECLASSMACHINE_H

#include "ELinkedList.h"
#include "ecore.h"

template <class Parent>
class EClassMachine {
 public:
  typedef uint32 State;
  typedef void (Parent::*Slot)(void);
  typedef bool (Parent::*Signal)(void);
  EClassMachine(Parent *parent = null);
  void setParent(Parent *parent) { _parent = parent; };
  State addState(Slot slot, bool repeat = true);
  void addTransition(State state, State next, Signal signal = null);
  void begin(State state) { _current = state; };
  State state() const { return _current; };
  void update();

 private:
  struct StatePrivate {
    State number;
    Slot slot;
    bool repeat;
    bool repeated;
    ELinkedList<Signal> signals;
    ELinkedList<State> nextState;
  };
  ELinkedList<StatePrivate> _states;
  State _current;
  Parent *_parent;
};

template <class Parent>
EClassMachine<Parent>::EClassMachine(Parent *parent) {
  _parent = parent;
  _current = 0;
}

template <class Parent>
typename EClassMachine<Parent>::State EClassMachine<Parent>::addState(
    Slot slot, bool repeat) {
  int number = _states.size();
  StatePrivate state;
  state.number = number;
  state.slot = slot;
  state.repeat = repeat;
  state.repeated = false;
  _states.append(state);
  return number;
}

template <class Parent>
void EClassMachine<Parent>::addTransition(State state, State nextState,
                                          Signal signal) {
  _states[state].nextState.append(_states[nextState].number);
  _states[state].signals.append(signal);
}

template <class Parent>
void EClassMachine<Parent>::update() {
  if (_states.size() > 0) {
    StatePrivate *current = &_states[_current];
    if (current->repeat || !current->repeated) {
      (_parent->*(current->slot))();
      current->repeated = true;
    }
    const int numberOfTransitions = current->signals.size();
    for (int i = 0; i < numberOfTransitions; ++i) {
      if (current->signals.at(i) != null) {
        if ((_parent->*(current->signals.at(i)))()) {
          _current = current->nextState.at(i);
          current->repeated = false;
        }
      } else {
        _current = current->nextState.at(i);
        current->repeated = false;
      }
    }
  }
}

#endif  // ECLASSMACHINE_H
