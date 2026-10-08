#include "Arduino.h"
#include "kernel.h"
#include "config.h"
#include "core.h"
#include "input.h"

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
}

void change_state(State newState) {
  currentContext.currentState = newState;
  currentContext.timeEnteredInState = millis();
}

State get_current_state() {
  return currentContext.currentState;
}

long get_current_time_in_state() {
  return millis() - currentContext.timeEnteredInState; 
}

long get_entered_state_time() {
  return currentContext.timeEnteredInState;
}

void LOG(const String& messageAddress) {
  // TODO: log to LCD
}


//helpers

Player player_create(short playerNumber) {
  Player player;

  player.playerNumber = playerNumber;
  assign_pins_to_player(player);
  player.score = 0;

  return player;
}

void led_fade(short ledPin, int &currentPulseValue, short &fadeAmount) {

  if(currentPulseValue + fadeAmount > 255 || currentPulseValue - fadeAmount < 0) {
    fadeAmount = -fadeAmount;
  } 

  int value = currentPulseValue + fadeAmount;
  analogWrite(ledPin, value);
}

void led_turn_off(short ledPin) {
  digitalWrite(ledPin, LOW);
}











