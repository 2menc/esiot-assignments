#include "Arduino.h"
#include "input.h"
#include "config.h"
#include "core.h"

#define DEBOUNCE_TIME 100 //ms


void leds_init(short redPin, short greenPin) {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void buttons_init(short pin) {
  pinMode(pin, INPUT);
}

bool read_digital(short fromPin) {
  int read = digitalRead(fromPin);

  return read > 0;
}

bool is_button_pressed(short buttonIndex) {
  return read_digital(buttonIndex);
}

void input_init(Player players[NUMBER_OF_PLAYERS]) {

  for(short i = 0; i < NUMBER_OF_PLAYERS; i++) {
    leds_init(players[i].redLedPin, players[i].greenLedPin);
    buttons_init(players[i].buttonPin);
  }
}
