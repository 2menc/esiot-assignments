#include "ServoMotor.h"

ServoMotor::ServoMotor(short pin) : pin(pin), currentAngle(0) {
  this->servo.attach(pin);
  pinMode(pin, OUTPUT);
}

void ServoMotor::moveTo(int angle) {
  servo.write(angle); // < than 180, gets parsed as an angle
  this->currentAngle = angle;
}

int ServoMotor::getCurrentAngle() {
  return this->currentAngle;
}

void ServoMotor::stop() {
  servo.write(this->currentAngle);
}
