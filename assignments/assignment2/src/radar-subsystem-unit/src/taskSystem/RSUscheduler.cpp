#include "RSUscheduler.h"

RSUscheduler::RSUscheduler() : numTasks(0) {}

bool RSUscheduler::registerTask(Task* task) {
  if(numTasks < MAX_TASKS) {
    tickables[numTasks] = task;
    return true;
  }
  return false;
}

void RSUscheduler::run() {
  this->tickAll();
}

void RSUscheduler::tickAll() {
  for(int i = 0; i < MAX_TASKS; i++) {
    tickables[i]->tick();
  }
}
