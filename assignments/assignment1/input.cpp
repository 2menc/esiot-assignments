#include "pins_arduino.h"
#include "Arduino.h"
#include "input.h"
#include "config.h"
#include "core.h"

#define DEBOUNCE_TIME 100 //ms

bool buttonsPressed[NUMBER_OF_PLAYERS] = {false, false};
long lastPressedTimes[NUMBER_OF_PLAYERS] = {0, 0};

void button_handler0(){ button_handler(0); }
void button_handler1(){ button_handler(1); }
void (*button_handlers[NUMBER_OF_PLAYERS])() = { button_handler0, button_handler1 };
void button_handler(short buttonIndex) {

  long timeStamp = millis();

  if(timeStamp - lastPressedTimes[buttonIndex] > DEBOUNCE_TIME) {

    buttonsPressed[buttonIndex] = true;
    lastPressedTimes[buttonIndex] = timeStamp; 
  }
}

void leds_init(short redPin, short greenPin) {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void buttons_init(short pin) {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), button_handlers[pin-1], RISING);
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

void input_reset() {
  long timeStamp = millis();

  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    buttonsPressed[i] = false;
    lastPressedTimes[i] = timeStamp;
  }
}

short get_difficulty() {
  int read = analogRead(POTENTIOMETER_PIN);
  short mappedReading = map(read, 0, 2^10, 1, 4);
  return mappedReading;
}











