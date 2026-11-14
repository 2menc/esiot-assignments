#include "UI.h"

UI::UI(unsigned int period, Screen* lcd, Light* redLed, Light* greenLed)
    : Task(period), lcd(lcd), redLed(redLed), greenLed(greenLed),
      blinkState(LedState::ALARM_LED_OFF), blinkTicks(0), state(State::IDLE),
      sector(0), distance(0) {
}

void UI::init() {
  this->redLed->turnOff();
  this->greenLed->turnOff();

  this->lcd->turnOn();
  this->blinkState = LedState::ALARM_LED_OFF;
  this->blinkTicks = 0;
}

void UI::tick() {
  // do/
  if(this->state == State::IDLE) {
    this->greenLed->turnOn();
    this->showInfo();
  }

  switch (this->blinkState) {
    case LedState::ALARM_LED_OFF:
      if(this->state == State::ALARM && this->blinkTicksPassed()) {
        this->blinkState = LedState::ALARM_LED_ON;
      } else if(this->state == State::PRE_ALARM) {
        this->blinkState = LedState::ALARM_LED_ON;
      }
      this->lastBlinkTime = millis();
      break;
    case LedState::ALARM_LED_ON:
      if(this->state == State::WORKING ||
          this->state == State::IDLE
      ) {
        this->blinkState = LedState::ALARM_LED_OFF;  
      } else if(this->state == State::ALARM 
        && this->blinkTicksPassed()
      ) {
        this->blinkState = LedState::ALARM_LED_OFF;
        }
      break;
  }
}

bool UI::blinkTicksPassed() {
  return (millis() - this->lastBlinkTime) >= this->blinkTicks;
}

void UI::showInfo() {
  this->lcd->setText("Sector: " + (String)this->sector +  
    "|Measure: " + (String)this->distance + "cm");
}

void UI::setMeasure(Measure measure) {
  this->sector = measure.sector;
  this->distance = measure.distance;
}

void UI::setState(State newState) {
  this->state = newState;
}