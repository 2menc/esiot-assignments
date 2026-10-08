#pragma once

#define NUMBER_OF_PLAYERS 2

typedef enum {
  STATE_WAITING_FOR_PLAYERS,
  STATE_SLEEP,
  TATE_PLAY,
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

