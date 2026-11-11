#include "UI.h"

UI::UI(unsigned int period, Screen* lcd, Light* redLed, Light* greenLed)
    : Task(period), lcd(lcd), redLed(redLed), greenLed(greenLed),
      blinkState(LedState::ALARM_LED_OFF), blinkTicks(0), state(State::IDLE),
      sector(0), distance(0) {
}

void UI::init() {
}

void UI::tick() {
}

void UI::setState(State state) {
}

void UI::setMeasure(Measure measure) {
}

void UI::blink(Light* led) {
}
