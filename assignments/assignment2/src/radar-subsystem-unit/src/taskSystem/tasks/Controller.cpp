#include "Controller.h"

Controller::Controller(unsigned int period, Input* input, Radar* radar, UI* ui, Communication* communication)
  : Task(period), 
    input(input), radar(radar), ui(ui), communication(communication),
    currentState(State::IDLE), currentSpeed(0), controlMode(ControlMode::NONE),
    remote(false), potAngle(0), targetAngle(0), temperature(20), remoteAngle(0) {
}

void Controller::init() { }

void Controller::tick() {
  switch (this->currentState)
    case State::IDLE: 
      if(this->input->getButtonEvent() == ButtonEvent::START) {
        this->enterWorking();
      }
      break;

    case State::WORKING:
      this->dists[this->radar->getMeasure().sector] = this->radar->getMeasure().distance;

      if(this->input->getButtonEvent() == ButtonEvent::STOP) { this->enterIdle(); } 
      else if(this->getCurrentMinDistance() >= D1 && this->getCurrentMinDistance() < D2) {
        this->enterPreAlarm();
      } else if(this->getCurrentMinDistance() < D1) { this->enterAlarm(); }
      break;

    case State::PRE_ALARM:
      this->dists[this->radar->getMeasure().sector] = this->radar->getMeasure().distance;

      if(this->getCurrentMinDistance() < D1) { this->enterAlarm(); }
      else if(this->getCurrentMinDistance() >= D2 
        || this->getCurrentMinDistance() > MAX_DIST) { this->enterWorking(); }
      else if(this->input->getButtonEvent() == ButtonEvent::STOP) { this->enterIdle(); }
      break;

    case State::ALARM:
      this->targetAngle = this->remote? this->remoteAngle : this->potAngle;
      
      break;
}


int Controller::getCurrentMinDistance() {
  return -1;
}

void Controller::sleep() {
}

void Controller::enterIdle() {
  this->radar->setControlMode(ControlMode::NONE);
  this->dists = [];
}
void Controller::enterWorking();
void Controller::enterPreAlarm();
void Controller::enterAlarm();
