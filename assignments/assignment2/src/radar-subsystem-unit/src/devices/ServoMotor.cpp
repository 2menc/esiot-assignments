#include "ServoMotor.h"

ServoMotor::ServoMotor(short pin) : pin(pin), currentAngle(0) {
}

void ServoMotor::moveTo(int angle) {
}

int ServoMotor::getCurrentAngle() {
  return currentAngle;
}

void ServoMotor::stop() {
}
