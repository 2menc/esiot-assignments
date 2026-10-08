#ifndef __CORE__
#define __CORE__

#include "config.h"

typedef enum {
  STATE_WAITING_FOR_PLAYERS,
  STATE_SLEEP,
  STATE_PLAY,
  STATE_END_ROUND,
  STATE_END_GAME
} State;

typedef enum {
  EVENT_NONE,
  EVENT_BUTTON_PRESSED
} Event;

typedef struct {
  short playerNumber;
  int score;

  short greenLedPin;
  short redLedPin;
  short buttonPin;
} Player;

typedef struct {
  State currentState;
  Event currentEvent;

  short difficulty;

  Player players[NUMBER_OF_PLAYERS];
} Context;


// STATE HANDLERS

void core_init();

void handle_current_state(State currentState);
void handle_event(Event occuredEvent);

void handle_state_waitingForPlayers();
void handle_state_sleep();
void handle_state_play();
void handle_state_endRound();
void handle_state_endGame();


#endif
