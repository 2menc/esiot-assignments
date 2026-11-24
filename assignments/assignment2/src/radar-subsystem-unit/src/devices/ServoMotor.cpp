#include "ServoMotor.h"

ServoMotor::ServoMotor(short pin) : pin(pin), currentAngle(0) {
  this->servo.attach(pin);
  pinMode(pin, OUTPUT);
}

void ServoMotor::moveTo(int angle) {
  // write first, so when the servo is attached again it goes straight to the new angle
  this->servo.write(angle);
  if (!this->servo.attached()) {
    this->servo.attach(this->pin);
  }
  this->currentAngle = angle;
}

int ServoMotor::getCurrentAngle() {
  return this->currentAngle;
}

void ServoMotor::stop() {
  this->servo.detach();
}
