#include "pins_arduino.h"
#include "Arduino.h"
#include "input.h"
#include "config.h"
#include "core.h"
#include "stateHandler.h"

#define DEBOUNCE_TIME 100 //ms

buttonsPressed = {false, false};
lastPressedTimes = {0, 0};

void leds_init(short redPin, short greenPin) {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void buttons_init(short pin) {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), button_handler, RISING);
}

bool read_digital(short fromPin) {
  int read = digitalRead(fromPin);

  return read > 0;
}

bool is_button_pressed(short buttonIndex) {
  return buttonsPressed[buttonIndex];
}

void input_init(Player players[NUMBER_OF_PLAYERS]) {

  for(short i = 0; i < NUMBER_OF_PLAYERS; i++) {
    leds_init(players[i].redLedPin, players[i].greenLedPin);
    buttons_init(players[i].buttonPin);
  }
}

void button_handler(short buttonIndex) {

  long timeStamp = millis()

  if(timeStamp - lastPressedTimes[button_handler] > DEBOUNCE_TIME) {

    buttonsPressed[buttonIndex] = true;
    lastPressedTimes[buttonIndex] = timeStamp; 
  }
}

void input_reset() {
  long timeStamp = millis();

  for(int i = 0; i < sizeof(buttonsPressed)/sizeof(long); i++) {
    buttonsPressed[i] = false;
    lastPressedTimes[i] = timeStamp;
  }
}












