#include "Controller.h"

#include "avr/sleep.h"

Controller::Controller(unsigned int period, Input* input, Radar* radar, UI* ui, Communication* communication)
  : Task(period), 
    input(input), radar(radar), ui(ui), communication(communication),
    currentState(State::IDLE), currentSpeed(0), controlMode(ControlMode::NONE),
    remote(false), potAngle(0), targetAngle(0), temperature(20), remoteAngle(0) {
}

void Controller::init() { }

void Controller::tick() {
  this->potAngle = this->input->getPotAngle();
  this->temperature = this->input->getTemperature();
  this->radar->setTemperature(this->temperature);

  const ButtonEvent currEvent = this->input->getButtonEvent();

  if (this->radar->hasNewMeasure()) {
    const Measure m = this->radar->getMeasure();
    this->dists[m.sector] = m.detected ? m.distance : -1;
    this->ui->setMeasure(m);
    this->communication->sendSectorToCSU(m);
  }

  const int minDist = this->getCurrentMinDistance();

  bool reset = currEvent == ButtonEvent::RESET;

  switch(this->currentState) {
    case State::IDLE: 
      if(currEvent == ButtonEvent::START) {
        this->enterWorking();
      } else {
        this->sleep();
      }
      break;

    case State::WORKING:
      if(currEvent == ButtonEvent::STOP) { this->enterIdle(); } 
      else if(minDist >= D1 && minDist < D2) {
        this->enterPreAlarm();
      } else if(minDist >= 0 && minDist < D2) { this->enterAlarm(); }
      break;

    case State::PRE_ALARM:
      if(currEvent == ButtonEvent::STOP) { this->enterIdle(); }
      else if (minDist >= 0 && minDist < D1) { this->enterAlarm(); } 
      else if (minDist < 0 || minDist >= D2) { this->enterWorking(); }
        
      break;

    case State::ALARM:
      if(this->communication->hasCommand()) {
        const Command cmd = this->communication->getCommand();

        if (cmd.type == CommandType::TAKE) {
          this->remote = true;
        } else if (cmd.type == CommandType::RELEASE) {
          this->remote = false;
        } else if (cmd.type == CommandType::ANGLE && isBetween(cmd.value, 0, 180)) {
          this->remoteAngle = cmd.value;
        } else if (cmd.type == CommandType::RESET) {
          reset = true;
        }
      }
      
      if(reset) {
        this->resetDists();
        this->enterWorking();
      } else {
        this->targetAngle = this->remote ? this->remoteAngle : this->potAngle;
        this->radar->setTargetAngle(this->targetAngle);
      }

      break;
  }
}


int Controller::getCurrentMinDistance() {
  int min = 1000;
  for(int i: this->dists) {
    if(i < min) { min = i; }
  }

  return min > 0 ? min : -1;
}

void Controller::sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // deep sleep
  sleep_enable();
  sleep_mode();

  /* only reacts to interrupts */

  sleep_disable();
}

void Controller::enterIdle() {
  this->radar->setControlMode(ControlMode::NONE);
  this->resetDists();
  this->sleep();
  this->changeState(State::IDLE);
}

void Controller::enterWorking() {
  this->controlMode = ControlMode::AUTO;
  this->currentSpeed = S1;
  this->changeState(State::WORKING);
}

void Controller::enterPreAlarm() {
  this->radar->setControlMode(ControlMode::AUTO);
  this->currentSpeed = S2;
  this->changeState(State::PRE_ALARM);
}

void Controller::enterAlarm() {
   this->radar->setControlMode(ControlMode::MANUAL);
   this->remote = false;
  this->changeState(State::ALARM);
}
  
bool Controller::isBetween(int value, int left, int right) {
  return value >= left && value <= right;
}

void Controller::resetDists() {
  for(int i = 0; i < NUM_SECTORS; i++) {
    this->dists[i] = -1;
  }
}

void Controller::changeState(State newState) {
  this->currentState = newState;
  this->ui->setState(newState);
  this->communication->sendStateToCSU(newState);
}