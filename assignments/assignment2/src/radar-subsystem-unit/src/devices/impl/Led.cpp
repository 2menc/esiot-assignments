#include "Led.h"
#include <Arduino.h>

Led::Led(short pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void Led::turnOn() {
    digitalWrite(this->pin, HIGH);
}

void Led::turnOff() {
    digitalWrite(this->pin, LOW);
}
