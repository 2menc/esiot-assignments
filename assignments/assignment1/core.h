#ifndef __CORE__
#define __CORE__

#include "Arduino.h"

#define NUMBER_OF_PLAYERS 2

#define WAITING_TIMEOUT 5000 //ms

#define MAX_NUMBER 3

const String MESSAGE_WAITING = "Welcome to React! Game. Press Buttons To Start";
const String MESSAGE_GO = "GO!";
const String MESSAGE_TIE = "Game Over - Tie";
const String MESSAGE_WINNER = "Game Over - The winner is ";

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

  short timesPressed;
} Player;

typedef struct {
  State currentState;
  Event currentEvent;
  long timeEnteredInState;

  short difficulty;

  Player players[NUMBER_OF_PLAYERS];
} Context;


// STATE HANDLERS
#include "config.h"

void core_init();

void handle_current_state(Context &currentContext);
void handle_event(Event occuredEvent);

void handle_state_waitingForPlayers(Context &ctx);
void handle_state_sleep(Context ctx);
void handle_state_play(Context &ctx);
void handle_state_endRound(Context &ctx);
void handle_state_endGame(Context &ctx);

uint8_t get_random_number();

#endif
