#include "Input.h"

Input::Input(unsigned int period, Button* start, Button* stop, Button* reset,
             AngleSensor* pot, TemperatureSensor* tempSensor)
    : Task(period), pot(pot), tempSensor(tempSensor),
      lastEvent(ButtonEvent::NONE), potAngle(0), temperature(0) {
  buttons[0] = start;
  buttons[1] = stop;
  buttons[2] = reset;
}

void Input::init() {
  // discard presses recorded before the system started
  for (int i = 0; i < NUM_BUTTONS; i++) {
    this->buttons[i]->wasPressed();
  }
}

void Input::tick() {
  this->temperature = this->tempSensor->getTemperature();
  this->potAngle = this->pot->getAngle();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (this->buttons[i]->wasPressed()) {
      switch (i) {
        case INDEX_BUTTON_START: this->lastEvent = ButtonEvent::START; break;
        case INDEX_BUTTON_STOP:  this->lastEvent = ButtonEvent::STOP;  break;
        case INDEX_BUTTON_RESET: this->lastEvent = ButtonEvent::RESET; break;
      }
    }
  }
}

float Input::getTemperature() {
  return this->temperature;
}

ButtonEvent Input::getButtonEvent() {
  const ButtonEvent e = this->lastEvent;
  this->lastEvent = ButtonEvent::NONE;

  return e;
}

int Input::getPotAngle() {
  return this->potAngle;
}
