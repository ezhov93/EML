/*
 * @file   ETask.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Task scheduler source file. Based on millis()/micros()
 */
 
#include "ETask.h"

ETask::ETask(uint32 taskQuantity) {
  _taskQuantity = taskQuantity;
  _taskQueue = new Task[_taskQuantity];
  _queueTail = 0;
}

ETask::~ETask() {
  delete[] _taskQueue;
}

void ETask::addTask(func_ptr task, int period, int delay) {
  for(int cnt= 0; cnt < _queueTail; ++cnt) {
    if(_taskQueue[cnt].task == task) {
      _taskQueue[cnt].timer = millis();
      _taskQueue[cnt].period = period; 
      _taskQueue[cnt].delay = delay-period?delay-period:0;
      return;  
    }
  }
  if (_queueTail < _taskQuantity) {
    _taskQueue[_queueTail].task = task;
    _taskQueue[_queueTail].timer = millis();
    _taskQueue[_queueTail].period = period;  
    _taskQueue[_queueTail].delay = delay;
    _queueTail++; 
  }
}

void ETask::deleteTask(func_ptr task) {
   for (int cnt=0; cnt<_queueTail; ++cnt) {
     if(_taskQueue[cnt].task == task) {
       if(cnt != (_queueTail - 1)) {
         _taskQueue[cnt].task = _taskQueue[_queueTail - 1].task;
         _taskQueue[cnt].timer = _taskQueue[_queueTail - 1].timer;
         _taskQueue[cnt].period = _taskQueue[_queueTail - 1].period;
         _taskQueue[cnt].delay = _taskQueue[_queueTail - 1].delay;
       }
       _queueTail--;                               
       return;
     }
   }
}

void ETask::update() {  
  for (int cnt=0; cnt<_queueTail; ++cnt) {
    if (_taskQueue[cnt].isReady()) {
      _taskQueue[cnt].task();
      _taskQueue[cnt].delay = 0;
      if(_taskQueue[cnt].period <= 0)
        deleteTask(_taskQueue[cnt].task);
    }
  }
}

bool ETask::Task::isReady() {
  if ((millis() - timer) >= (period+delay)) {
    timer = millis();
    return true;    
  }
  else 
    return false;
}
