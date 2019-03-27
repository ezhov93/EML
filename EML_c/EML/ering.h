/*
 * @file   ering_private.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Simple circular buffer module.
 */

#ifndef ERING_H
#define ERING_H

#include "etypes.h"

typedef struct ERingType
{
  __IO byte *data;
  __IO int size;
  __IO int tail;
  __IO int head;
};

bool ERing_IsFull(ERingType *obj);
bool ERing_IsEmpty(ERingType *obj);
bool ERing_Push(ERingType *obj, void *data, int size);
bool ERing_Pop(ERingType *obj, void *data, int size);  
bool ERing_Peek(ERingType *obj, void *data, int size);
void ERing_Clear(ERingType *obj);
int ERing_Count(ERingType *obj);

#endif // ERINGPRIVATE_H
