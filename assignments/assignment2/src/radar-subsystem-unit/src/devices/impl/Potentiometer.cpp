#include "Potentiometer.h"
#include "model/config.h"

#include <Arduino.h>

Potentiometer::Potentiometer(short pin) : pin(pin) {
  pinMode(pin, INPUT);
}

int Potentiometer::getAngle() {
  return this->convertVToAngle(this->measureTension());
}

int Potentiometer::convertVToAngle(float V) {
  return (int) (V / 5.0f * 180);  // 0..5 V -> 0..180 degrees
}

float Potentiometer::measureTension() {
  return analogRead(this->pin) * TENSION_MAPPING_FACTOR;
}