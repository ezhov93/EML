/*
 * @file   ering.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer template class.
 */

#ifndef ERING_H
#define ERING_H

#include "etypes.h"
#include "ering_private.h"
 
template <typename T=byte, int SIZE=64> 
class ERing {
public:
  ERing() {
    ring.data = data;
    ring.size = SIZE;
    ERingPrivate::clear(ring);
  }
  bool isFull() {
   return ERingPrivate::isFull(ring);
  }
  
  bool isEmpty() {
    return ERingPrivate::isEmpty(ring);
  }
  
  void push(T data) {
    ERingPrivate::push(ring, (void*)data, sizeof(T));
  }
  
  void push(T &data, int size) {
    ERingPrivate::push(ring, data, sizeof(T)*size);
  }
  
  T pop() {
    T data;
    ERingPrivate::pop(ring, data, sizeof(T));
    return data;
  }
  
  void pop(T &data, int size) {
    ERingPrivate::pop(ring, data, sizeof(T)*size);
  }
  
  T peek() {
    T data;
    ERingPrivate::peek(ring, data, sizeof(T));
    return data;
  }
  
  void peek(T &data, int size) {
    ERingPrivate::peek(ring, data, sizeof(T)*size);
  }
  
  void clear() { 
    ERingPrivate::clear(ring);
  }
  
  int size() const {
    return SIZE;
  }
  
  int count() {
    return ERingPrivate::count(ring);
  }
  
  void *data_ptr() const {
      return (void*)data;
  }

private:
  ERingPrivateType ring;
#pragma pack(push,1)
  byte data[SIZE];
#pragma pack(pop)
};



#endif // ERINGBUFFER_H
