#include "RSUscheduler.h"
#include <Arduino.h>

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
  for (int i = 0; i < this->numTasks; i++) {
    this->tickables[i]->update(now);
  }
}
