#include "Potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(short pin) : pin(pin) {
}

int Potentiometer::getAngle() {
  return 0;
}

int Potentiometer::convertVToAngle(float V) {
  return 0;
}
