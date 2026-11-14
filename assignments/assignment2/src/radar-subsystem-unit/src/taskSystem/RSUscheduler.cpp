#include "RSUscheduler.h"
#include <TimerOne.h>

RSUscheduler::RSUscheduler() : numTasks(0) {}

bool RSUscheduler::registerTask(Task* task) {
  if(this->numTasks < MAX_TASKS) {
    tickables[this->numTasks++] = task;
    return true;
  }
  return false;
}

void RSUscheduler::run() {
  this->tickAll();
}

void RSUscheduler::tickAll() {
  const unsigned long now = millis();
  for (Task* t: this->tickables) {
    t->update(now);
  }
}
