#include "TactileButton.h"
#include <Arduino.h>

TactileButton::TactileButton(short pin) : pin(pin) {
}

bool TactileButton::isPressed() {
  return false;
}
