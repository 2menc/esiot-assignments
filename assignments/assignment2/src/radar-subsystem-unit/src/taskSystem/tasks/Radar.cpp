#include "Radar.h"

Radar::Radar(unsigned int period, DistanceSensor* sonar, ServoMotor* servo)
    : Task(period), sonar(sonar), servo(servo), state(RadarState::STOPPED),
      sector(0), dir(1), ticks(0), controlMode(ControlMode::NONE),
      temperature(20), currentSpeed(1), targetAngle(0),
      lastMeasure({false, 0, 0}), newMeasure(false) {
}

void Radar::init() {
}

void Radar::tick() {
}

void Radar::setControlMode(ControlMode mode) {
}

void Radar::setSpeed(int speed) {
}

void Radar::setTemperature(float temperature) {
}

void Radar::setTargetAngle(int angle) {
}

bool Radar::hasNewMeasure() {
  return newMeasure;
}

Measure Radar::getMeasure() {
  return lastMeasure;
}

int Radar::convertSectorToAngle(int sector) {
  return 0;
}
