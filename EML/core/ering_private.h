/*
 * @file   ering_private.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer static private class.
 */

#ifndef ERINGPRIVATE_H
#define ERINGPRIVATE_H

#include "etypes.h"

namespace EPrivate {
  struct ERingPrivate {
    __IO byte *data;
    __IO int size;
    __IO int tail;
    __IO int head;
    static bool isFull(ERingPrivate &obj);
    static bool isEmpty(ERingPrivate &obj);
    static bool push(ERingPrivate &obj, void *data, int size);
    static bool pop(ERingPrivate &obj, void *data, int size);  
    static bool peek(ERingPrivate &obj, void *data, int size);
    static void clear(ERingPrivate &obj);
    static int count(ERingPrivate &obj);
  };
}



#endif // ERINGPRIVATE_H
