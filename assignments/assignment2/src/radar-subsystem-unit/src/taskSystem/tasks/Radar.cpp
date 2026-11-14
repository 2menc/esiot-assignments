#include "Radar.h"

Radar::Radar(unsigned int period, DistanceSensor* sonar, ServoMotor* servo)
    : Task(period), sonar(sonar), servo(servo), state(RadarState::STOPPED),
      sector(0), dir(1), ticks(0), controlMode(ControlMode::NONE),
      temperature(20), currentSpeed(1), targetAngle(0),
      lastMeasure({false, 0, 0}), newMeasure(false) {
}

void Radar::init() {
  this->state = RadarState::STOPPED;
}

void Radar::tick() {

  switch (this->state)
  {
    case RadarState::STOPPED:
      if(this->controlMode == ControlMode::AUTO) {
        this->sector = 0;
        this->dir = +1;
        this->enterMoving();
      }
      break;
    
    case RadarState::MOVING:
      this->ticks++;
      if(this->ticks >= this->currentSpeed) {  //has moved
        this->enterMeasuring();
      }
      break;
    
    case RadarState::MEASURING:
      if(this->controlMode == ControlMode::AUTO) {
        if(this->sector + this->dir < 0 || this->sector + this->dir >= NUM_SECTORS) {
          this->dir = -this->dir;
        }        
        this->sector += this->dir;
        this->enterMoving();
      } else if(this->controlMode == ControlMode::NONE) {
        this->changeState(RadarState::STOPPED); 
      } else if(this->controlMode == ControlMode::MANUAL) {
        this->changeState(RadarState::MANUAL);
      }
      break;

    case RadarState::MANUAL:
      if(this->controlMode == ControlMode::AUTO) {
        this->sector = 0;
        this->dir = +1;
        
        this->enterMoving();
      } else if(this->controlMode == ControlMode::NONE) {
        this->changeState(RadarState::STOPPED);
      } else {
        this->servo->moveTo(this->targetAngle);
      }
      break;
  }   
}

void Radar::setControlMode(ControlMode mode) {
  this->controlMode = mode;
}

void Radar::setSpeed(int speed) {
  this->currentSpeed = speed;
}

void Radar::setTemperature(float temperature) {
  this->temperature = temperature;
}

void Radar::setTargetAngle(int angle) {
  this->targetAngle = angle;
}

bool Radar::hasNewMeasure() {
  return this->newMeasure;
}

Measure Radar::getMeasure() {
  this->newMeasure = false;
  return this->lastMeasure;
}

int Radar::convertSectorToAngle(int sector) {
  const int width = 180 / NUM_SECTORS;
  return sector * width + width / 2;  // centwr
}

void Radar::changeState(RadarState state) {
  this->state = state;
}

void Radar::enterMeasuring() {
  const int d = this->sonar->getDistance(this->temperature);

  this->lastMeasure = {d >= 0, this->sector, d};
  this->newMeasure = true;

  this->changeState(RadarState::MEASURING);
}

void Radar::enterMoving() {
  this->servo->moveTo(this->convertSectorToAngle(this->sector));
  this->ticks = 0;

  this->changeState(RadarState::MOVING);
}
