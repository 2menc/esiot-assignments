#include "Task.h"
#include "TimerOne.h"

Task::Task(unsigned int period) : period(period), lastTickTime(0) {}

void Task::update(unsigned long now) {
    if(now - lastTickTime >= period) {
        this->lastTickTime = now;
        this->tick();
    }
}
