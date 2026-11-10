#include "AnalogTemperatureSensor.h"
#include <Arduino.h>

AnalogTemperatureSensor::AnalogTemperatureSensor(short pin) : pin(pin) {
}

float AnalogTemperatureSensor::getTemperature() {
  return 0;
}

float AnalogTemperatureSensor::convertVtoTemp(float V) {
  return 0;
}
