#include "AnalogTemperatureSensor.h"

#include <Arduino.h>
#include "../../model/config.h"

AnalogTemperatureSensor::AnalogTemperatureSensor(short pin) : pin(pin) {
  pinMode(pin, INPUT);
}

float AnalogTemperatureSensor::getTemperature() {
  return this->convertVtoTemp(this->getTension());
}

float AnalogTemperatureSensor::getTension() {
  const float value = analogRead(this->pin);

  return value * TENSION_MAPPING_FACTOR;
}

float AnalogTemperatureSensor::convertVtoTemp(float V) {
  return V - 0.5f;
}

