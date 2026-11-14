#include <Arduino.h>

#include "model/config.h"
#include "taskSystem/RSUscheduler.h"
#include "taskSystem/tasks/Communication.h"
#include "taskSystem/tasks/Controller.h"
#include "taskSystem/tasks/Input.h"
#include "taskSystem/tasks/Radar.h"
#include "taskSystem/tasks/UI.h"
#include "taskSystem/tasks/Task.h"
#include "model/setupper.h"

RSUscheduler* scheduler;

void setup() {
    scheduler = new RSUscheduler();
    setupSystem(scheduler);
}

void loop() {
    scheduler->run();
}