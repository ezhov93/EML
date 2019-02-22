/*
 * @file   eringbuffer.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer class.
 */

#ifndef ETIMER_H_
#define ETIMER_H_

#include "etypes.h"
 
class ERingBuffer {
  public:
    ERingBuffer(void *data, int size);
    

  private:
    __IO uint8 *_data;
    __IO uint16 _head;     
    __IO uint16 _tail;         
    __IO uint16 _size;         
};

#endif
