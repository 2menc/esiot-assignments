#include "Arduino.h"
#include "kernel.h"
#include "config.h"
#include "core.h"
#include "input.h"
#include "view.h"

Player player_create(short playerNumber);

Context currentContext;

/* init should initialize the necessary structures to store players and context data*/
void kernel_init() {
  
  // players
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    currentContext.players[i] = player_create(i+1);
  }

  currentContext.currentEvent = EVENT_NONE;
  currentContext.currentState = STATE_WAITING_FOR_PLAYERS;
  currentContext.difficulty = get_difficulty();
  currentContext.timeEnteredInState = millis();

  // LCD
  lcd_init();
}

void change_state(State newState) {
  currentContext.currentState = newState;
  currentContext.timeEnteredInState = millis();
}

Context get_current_context() {
  return currentContext;
}

long get_current_time_in_state() {
  return millis() - currentContext.timeEnteredInState; 
}

long get_entered_state_time() {
  return currentContext.timeEnteredInState;
}

void LOG(const String& messageAddress) {
  short cursor[2] = {0, 0};
  display(messageAddress, cursor, DISPLAY_STATIC);
}


//helpers

Player player_create(short playerNumber) {
  Player player;

  player.score = 0;
  player.playerNumber = playerNumber;

  assign_pins_to_player(player);

  return player;
}

void led_fade(short ledPin, short &currentPulseValue, short &fadeAmount) {

  int nextValue = currentPulseValue + fadeAmount;

  if (nextValue > 255 || nextValue < 0) {    
    fadeAmount = -fadeAmount;
  } 

  currentPulseValue += fadeAmount;
  analogWrite(ledPin, currentPulseValue);
}

void led_turn_off(short ledPin) {
  digitalWrite(ledPin, LOW);
}











