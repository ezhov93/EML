/*
 * @file   ETask.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Task scheduler class. Based on millis()/micros()
 */

#ifndef ETASK_H
#define ETASK_H

#include "ecore.h"

class ETask {
  public:
    ETask(uint32 taskQuantity);
    ~ETask();
    void addTask(func_ptr task, int period = 0, int delay = 0);
    void deleteTask (func_ptr task);
    void update();
  private:
    struct Task { 
      func_ptr task; 
      uint32 timer; 
      int period;
      int delay;
      bool isReady();      
    };
    uint32 _taskQuantity;
    uint32 _queueTail;
    Task *_taskQueue;       
};

#endif // ETASK_H

