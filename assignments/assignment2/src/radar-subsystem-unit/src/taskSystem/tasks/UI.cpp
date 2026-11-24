#include "UI.h"
#include <Arduino.h>

UI::UI(unsigned int period, Screen* lcd, Light* redLed, Light* greenLed)
    : Task(period), lcd(lcd), redLed(redLed), greenLed(greenLed),
      blinkState(LedState::ALARM_LED_OFF), lastBlinkTime(0), state(State::IDLE),
      sector(0), distance(0), detected(false), stateChanged(false), measureChanged(false) {
}

void UI::init() {
  // IDLE: everything off
  this->redLed->turnOff();
  this->greenLed->turnOff();
  this->lcd->turnOff();

  this->blinkState = LedState::ALARM_LED_OFF;
  this->lastBlinkTime = millis();
}

void UI::tick() {
  // ON LED and display: switched on or off only when the state changes
  if (this->stateChanged) {
    this->stateChanged = false;

    if (this->state == State::IDLE) {
      this->greenLed->turnOff();
      this->lcd->turnOff();
    } else {
      this->greenLed->turnOn();
      this->lcd->turnOn();
      this->measureChanged = true;  // show the info as soon as the display is on
    }
  }

  // sector and distance: written only when a new measure arrived
  if (this->measureChanged && this->state != State::IDLE) {
    this->measureChanged = false;
    this->showInfo();
  }

  // ALARM LED FSM
  switch (this->blinkState) {
    case LedState::ALARM_LED_OFF:
      if (this->state == State::PRE_ALARM
          || (this->state == State::ALARM && this->blinkTicksPassed())) {
        this->redLed->turnOn();
        this->blinkState = LedState::ALARM_LED_ON;
        this->lastBlinkTime = millis();
      }
      break;

    case LedState::ALARM_LED_ON:
      if (this->state == State::WORKING || this->state == State::IDLE
          || (this->state == State::ALARM && this->blinkTicksPassed())) {
        this->redLed->turnOff();
        this->blinkState = LedState::ALARM_LED_OFF;
        this->lastBlinkTime = millis();
      }
      break;
  }
}

bool UI::blinkTicksPassed() {
  return millis() - this->lastBlinkTime >= LED_BLINK_PERIOD;
}

void UI::showInfo() {
  String text = "Sector ";
  text += this->sector + 1;  // the spec numbers sectors from 1
  text += "\n";

  if (this->detected) {
    text += this->distance;
    text += " cm";
  } else {
    text += "no object";
  }
  this->lcd->setText(text);
}

void UI::setMeasure(Measure measure) {
  this->sector = measure.sector;
  this->distance = measure.distance;
  this->detected = measure.detected;
  this->measureChanged = true;
}

void UI::setState(State newState) {
  if (newState != this->state) {
    this->state = newState;
    this->stateChanged = true;
  }
}
