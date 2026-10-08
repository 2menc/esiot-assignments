#include "core.h"

#define DEFAULT_BAUD_RATE 9600

void handle_current_state(Context currentContext) {
  
  switch(currentContext.currentState) {
    case STATE_WAITING_FOR_PLAYERS: handle_state_waitingForPlayers(currentContext);
    case STATE_SLEEP: handle_state_sleep(currentContext);
    case STATE_PLAY: handle_state_play(currentContext);
    case STATE_END_ROUND: handle_state_endRound(currentContext);
    case STATE_END_GAME: handle_state_endGame(currentContext);

    default: return;
  }
}

void handle_event(Context currentContext) {

  switch(currentContext.currentEvent) {
    case EVENT_NONE: return;
    case EVENT_BUTTON_PRESSED: {
      
    }
    default: return;
  }
}

void core_init() {
  Serial.begin(DEFAULT_BAUD_RATE);
}

void handle_state_waitingForPlayers(Context ctx) {
  
}
void handle_state_sleep(Context ctx);
void handle_state_play(Context ctx);
void handle_state_endRound(Context ctx);
void handle_state_endGame(Context ctx);


