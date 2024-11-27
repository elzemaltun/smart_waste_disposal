#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "timer.h"
#include "task.h"

#define MAX_TASKS 10

class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  Timer timer;

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif

