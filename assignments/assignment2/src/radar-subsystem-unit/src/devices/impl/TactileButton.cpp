#include "TactileButton.h"
#include <Arduino.h>

/* Use pin change interrupts on every pin, so a press can also wake the MCU from deep sleep.
 * EnableInterrupt.h defines the interrupt routines: include it in this file only. */
#define EI_NOTEXTERNAL
#include <EnableInterrupt.h>

TactileButton* TactileButton::instances[MAX_BUTTONS] = {nullptr, nullptr, nullptr};
int TactileButton::numInstances = 0;

void TactileButton::handler0() { instances[0]->handleInterrupt(); }
void TactileButton::handler1() { instances[1]->handleInterrupt(); }
void TactileButton::handler2() { instances[2]->handleInterrupt(); }

TactileButton::TactileButton(short pin) : pin(pin), pressed(false), lastChange(0) {
  static void (*const handlers[MAX_BUTTONS])() = {handler0, handler1, handler2};

  pinMode(pin, INPUT);
  if (numInstances < MAX_BUTTONS) {
    instances[numInstances] = this;
    enableInterrupt(pin, handlers[numInstances], CHANGE);
    numInstances++;
  }
}

void TactileButton::handleInterrupt() {
  const unsigned long now = millis();

  // a press counts only if the pin is on HIGH and was still for DEBOUNCE_TIME:
  // bounces, on press and on release, keep moving lastChange forward and are ignored
  if (digitalRead(pin) == HIGH && now - lastChange > DEBOUNCE_TIME) {
    pressed = true;
  }
  lastChange = now;
}

bool TactileButton::wasPressed() {
  noInterrupts();
  const bool result = pressed;
  pressed = false;
  interrupts();
  return result;
}
