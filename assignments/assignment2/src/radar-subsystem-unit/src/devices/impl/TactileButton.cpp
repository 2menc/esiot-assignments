#include "TactileButton.h"
#include <Arduino.h>

TactileButton::TactileButton(short pin) : pin(pin) {
  pinMode(pin, INPUT);
  this->lastTimePressed = 0;
}

bool TactileButton::isPressed() {
  const bool pressed = digitalRead(pin) == HIGH;
  const unsigned long timeEntered = millis();

  return pressed && timeEntered - lastTimePressed >= DEBOUNCE_TIME;
}
