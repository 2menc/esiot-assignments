#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(short triggerPin, short echoPin)
    : triggerPin(triggerPin), echoPin(echoPin) {
}

int UltrasonicSensor::getDistance(float temperature) {
  return -1;
}

void UltrasonicSensor::sendEcho() {
}

long UltrasonicSensor::readEchoTime() {
  return 0;
}
