#ifndef __CORE__
#define __CORE__

#include "Arduino.h"

#define NUMBER_OF_PLAYERS 2

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
#include "config.h"

void core_init();

void handle_current_state(State currentState);
void handle_event(Event occuredEvent);

void handle_state_waitingForPlayers(Context ctx);
void handle_state_sleep(Context ctx);
void handle_state_play(Context ctx);
void handle_state_endRound(Context ctx);
void handle_state_endGame(Context ctx);


#endif
