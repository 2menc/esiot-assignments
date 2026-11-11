#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(short triggerPin, short echoPin)
    : triggerPin(triggerPin), echoPin(echoPin), lastEcho(0), isSendingEcho(false) {
      pinMode(triggerPin, INPUT);
      pinMode(echoPin, OUTPUT);
}

int UltrasonicSensor::getDistance(float temperature) {
  return (SOUND_SPEED * this->readEchoTime() / 2) * 100;  // cm
}

void UltrasonicSensor::sendEcho() {
  analogWrite(echoPin, LOW);
}

void UltrasonicSensor::endEcho() {
  analogWrite(echoPin, LOW);
}

long UltrasonicSensor::readEchoTime() {
  unsigned long timeEntered = millis();

  if(!this->isSendingEcho) {
    this->lastEcho = timeEntered;
    this->sendEcho();
    this->isSendingEcho = true;
  } else if(this->isSendingEcho && 
      timeEntered - this->lastEcho >= ECHO_DELAY) {
    this->isSendingEcho = false;
    return timeEntered - this->lastEcho;
  }
}

