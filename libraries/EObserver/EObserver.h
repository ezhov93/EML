/*
 * @file   EObserver.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Observer/Subject template class.
 */

#ifndef EOBSERVER_H
#define EOBSERVER_H

#include "ELinkedList.h"

template <class T>
class EObserver {
 protected:
  explicit EObserver() = default;
  virtual ~Observer() = default;
  virtual void update(T *subject) = 0;
};

template <class T>
class ESubject {
 protected:
  explicit ESubject() = default;
  virtual ~ESubject() = default;
  void attach(EObserver<T> &observer) { _observers.append(&observer); }
  void detach(EObserver<T> &observer) {
    _observers.remove(_observers.indexOf(&observer));
  }
  void notify() {
    for (int i = 0; i < _observers.size(); ++i)
      _observers.at(i)->update((T *)(this));
  }

 private:
  ELinkedList<EObserver<T> *> _observers;
};

#endif  // EOBSERVER_H
