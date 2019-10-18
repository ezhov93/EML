/*
 * @file   ering.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer template class.
 */

#ifndef ERING_H
#define ERING_H

#include "ering_private.h"
#include "etypes.h"

template <typename T = byte>
class ERing {
 public:
  ERing(int size) {
    _ring.data = data;
    _ring.size = size;
    data = new data[size];
    EPrivate::ERingPrivate::clear(_ring);
  }

  ~ERing() { delete[] data; }

  bool isFull() { return EPrivate::ERingPrivate::isFull(_ring); }

  bool isEmpty() { return EPrivate::ERingPrivate::isEmpty(_ring); }

  void push(T data) {
    EPrivate::ERingPrivate::push(_ring, (void *)data, sizeof(T));
  }

  void push(T &data, int size) {
    EPrivate::ERingPrivate::push(_ring, data, sizeof(T) * size);
  }

  T pop() {
    T data;
    EPrivate::ERingPrivate::pop(_ring, data, sizeof(T));
    return data;
  }

  void pop(T &data, int size) {
    EPrivate::ERingPrivate::pop(_ring, data, sizeof(T) * size);
  }

  T peek() {
    T data;
    EPrivate::ERingPrivate::peek(_ring, data, sizeof(T));
    return data;
  }

  void peek(T &data, int size) {
    EPrivate::ERingPrivate::peek(_ring, data, sizeof(T) * size);
  }

  void clear() { EPrivate::ERingPrivate::clear(_ring); }

  int size() const { return SIZE; }

  int count() { return EPrivate::ERingPrivate::count(_ring); }

  void *data_ptr() const { return (void *)data; }

 private:
  EPrivate::ERingPrivate _ring;
  byte *_data;
  int _size;
};

#endif  // ERINGBUFFER_H
