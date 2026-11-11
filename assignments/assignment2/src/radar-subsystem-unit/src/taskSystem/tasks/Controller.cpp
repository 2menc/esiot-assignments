#include "Controller.h"

<<<<<<< HEAD
Controller::Controller(unsigned int period, Input* input, Radar* radar, UI* ui,
                       Communication* communication)
    : Task(period), input(input), radar(radar), ui(ui), communication(communication),
      currentState(State::IDLE), currentSpeed(0), controlMode(ControlMode::NONE),
      remote(false), potAngle(0), targetAngle(0), temperature(20), remoteAngle(0) {
=======
Controller::Controller(unsigned int period, Input* input, Radar* radar, UI* ui, Communication* communication)
  : Task(period), 
    input(input), radar(radar), ui(ui), communication(communication),
    currentState(State::IDLE), currentSpeed(0), controlMode(ControlMode::NONE),
    remote(false), potAngle(0), targetAngle(0), temperature(20), remoteAngle(0) {
>>>>>>> e60b204d38f7f0bc56ba00584d845085cf0ec7a4
}

void Controller::init() {
}

void Controller::tick() {
}

int Controller::getCurrentMinDistance() {
  return -1;
}

void Controller::sleep() {
}
