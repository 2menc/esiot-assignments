#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(short triggerPin, short echoPin)
    : triggerPin(triggerPin), echoPin(echoPin) {
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
}

int UltrasonicSensor::getDistance(float temperature) {
  this->sendEcho();

  const long microSeconds = pulseIn(this->echoPin, HIGH, ECHO_TIMEOUT_MICROS);
  if(microSeconds == 0) {return -1;}

  const float currentSoundSpeed = SOUND_SPEED + SOUND_SPEED_TEMPERATURE_FACTOR * temperature;

  return (int)(microSeconds/MICROS_IN_A_SECOND * currentSoundSpeed / 2 * 100); // cm
}

void UltrasonicSensor::sendEcho() {

  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
}

