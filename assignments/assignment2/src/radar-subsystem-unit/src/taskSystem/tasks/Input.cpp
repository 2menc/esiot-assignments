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
  for (int i = 0; i < NUM_BUTTONS; i++) {
    this->lastButtons[i] = this->buttons[i]->isPressed();
  }
}

void Input::tick() {
  this->temperature = this->tempSensor->getTemperature(); /*temperature*/
  this->potAngle = this->pot->getAngle(); /*angle*/

  // last event
  for(int i = 0; i < NUM_BUTTONS; i++) {
    this->lastButtons[i] = this->buttons[i]->isPressed();
  }
  for(int i = 0; i < NUM_BUTTONS; i++) {
    if(lastButtons[i]) {
      switch (i)
      {
      case INDEX_BUTTON_START: // start
        this->lastEvent = ButtonEvent::START;      
        break;
      case INDEX_BUTTON_STOP: // stop
        this->lastEvent = ButtonEvent::STOP;
        break;
      case INDEX_BUTTON_RESET: // reset
        this->lastEvent = ButtonEvent::RESET;
        break;
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
