/*
 * @file   ering_private.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer template class.
 */

#include "ering_private.h"

using namespace EPrivate;

bool ERingPrivate::isFull(ERingPrivate &obj) {
  return (obj.tail + 1 == obj.head) ||
         ((obj.tail == obj.size) && (obj.head == 0));
}

bool ERingPrivate::isEmpty(ERingPrivate &obj) { return obj.head == obj.tail; }

bool ERingPrivate::push(ERingPrivate &obj, void *data, int size) {
  byte *data_ptr = (byte *)data;
  bool status = true;
  for (int cnt = 0; cnt < size; ++cnt) {
    obj.data[obj.tail] = data_ptr[cnt];
    obj.tail = (++obj.tail == obj.size) ? 0 : obj.tail;
    if (ERingPrivate::isFull(obj)) status = false;
  }
  return status;
}

bool ERingPrivate::pop(ERingPrivate &obj, void *data, int size) {
  byte *data_ptr = (byte *)data;
  for (int cnt = 0; cnt < size; ++cnt) {
    if (ERingPrivate::isEmpty(obj)) return false;
    data_ptr[cnt] = obj.data[obj.head];
    obj.head = (++obj.head == obj.size) ? 0 : obj.head;
  }
  return true;
}

bool ERingPrivate::peek(ERingPrivate &obj, void *data, int size) {
  const int head = obj.head;
  bool status = ERingPrivate::pop(obj, data, size);
  obj.head = head;
  return status;
}

void ERingPrivate::clear(ERingPrivate &obj) { obj.head = obj.tail; }

int ERingPrivate::count(ERingPrivate &obj) {
  int cnt = obj.tail - obj.head;
  if (cnt < 0)
    return obj.size - obj.head + obj.tail - 1;
  else
    return cnt;
}
