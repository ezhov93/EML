/*
 * @file   EMachine.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  State machine class. Based on millis()/micros()
 */

#ifndef EMACHINE_H
#define EMACHINE_H

#include "ecore.h"
#include "ELinkedList.h"

class EMachine {
  public:
    typedef uint32 State;
    typedef void (*Slot)(void); 
    typedef bool (*Signal)(void); 
    EMachine();
    ~EMachine();
    State addState(Slot slot);
    void addTransition(State state, State next, Signal signal = null);
    void begin(State state); 
    State state();
    void update();
    
  private:
    struct StatePrivate { 
      State number; 
      Slot slot;
      ELinkedList<Signal> signals;
      ELinkedList<State> nextState; 
    };
    ELinkedList<StatePrivate> _states;
    State _current;
};

#endif // EMACHINE_H

