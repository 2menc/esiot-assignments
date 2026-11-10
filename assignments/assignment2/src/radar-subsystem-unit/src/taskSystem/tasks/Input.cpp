#include "Input.h"

Input::Input(int period, Button* start, Button* stop, Button* reset,
             AngleSensor* pot, TemperatureSensor* tempSensor)
    : Task(period), pot(pot), tempSensor(tempSensor),
      lastEvent(ButtonEvent::NONE), potAngle(0), temperature(0) {
  buttons[0] = start;
  buttons[1] = stop;
  buttons[2] = reset;
}

void Input::init() {
}

void Input::tick() {
}

float Input::getTemperature() {
  return temperature;
}

ButtonEvent Input::getButtonEvent() {
  return ButtonEvent::NONE;
}

int Input::getPotAngle() {
  return potAngle;
}
