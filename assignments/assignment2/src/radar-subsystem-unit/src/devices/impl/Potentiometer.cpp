#include "Potentiometer.h"
#include "config.h"

#include <Arduino.h>

Potentiometer::Potentiometer(short pin) : pin(pin) {
  pinMode(pin, INPUT);
}

int Potentiometer::getAngle() {
  return this->convertVToAngle(this->measureTension());
}

int Potentiometer::convertVToAngle(float V) {
  return map(V, 0, 1023, 0, 180);
}

float Potentiometer::measureTension() {
  return analogRead(this->pin) * TENSION_MAPPING_FACTOR;
}