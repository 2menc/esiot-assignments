#include "core.h"
#include "kernel.h"
#include "input.h"
#include <avr/sleep.h>
#include "view.h"

#define DEFAULT_BAUD_RATE 9600
#define FADE_FREQUENCY 25  //ms

void handle_current_state(Context currentContext) {

  switch (currentContext.currentState) {
    case STATE_WAITING_FOR_PLAYERS: handle_state_waitingForPlayers(currentContext); break;
    case STATE_SLEEP: handle_state_sleep(currentContext); break;
    case STATE_PLAY: handle_state_play(currentContext); break;
    case STATE_END_ROUND: handle_state_endRound(currentContext); break;
    case STATE_END_GAME: handle_state_endGame(currentContext); break;

    default: return;
  }
}

void handle_event(Context currentContext) {

  switch (currentContext.currentEvent) {
    case EVENT_NONE: return; break;
    case EVENT_BUTTON_PRESSED:
      {

        break;
      }
    default: return;
  }
}

void core_init() {
  Serial.begin(DEFAULT_BAUD_RATE);
}

unsigned long timeLastFade;
void handle_state_waitingForPlayers(Context ctx) {
  /*
  all green leds should be off and all red led should be pulsing 
  (fading in and out, when R1 is fading in, R2 should be fading out), 
  waiting for players to start the game;
  */

  //LOG("WAITING FOR PLAYERS");
  short cursor[2] = { 0, 0 };
  display(MESSAGE_WAITING, cursor, DISPLAY_ROLLING);

  static short currentFade[2] = { 0, 255 };
  static short fadeStep[2] = { 5, -5 };

  // turns off all green leds
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    led_turn_off(ctx.players[i].greenLedPin);
  }

  // red leds start to fade
  if (millis() - timeLastFade >= FADE_FREQUENCY) {  //non-blocking fade (no delay())
    timeLastFade = millis();
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
      led_fade(ctx.players[i].redLedPin, currentFade[i], fadeStep[i]);
    }
  }

  //TODO: LCD


  // wait for both buttons
  bool allPressed = true;
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if (!is_button_pressed(i)) {
      allPressed = false;
      break;
    }
  }

  // checks if time ran out
  if (get_current_time_in_state() >= WAITING_TIMEOUT) {
    input_reset();
    change_state(STATE_SLEEP);
    return;
  }
}

void handle_state_sleep(Context ctx) {

  LOG("SLEEP");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  //first thing: wake
  sleep_disable();

  LOG("WOKE UP");
  delay(700);
  change_state(STATE_WAITING_FOR_PLAYERS);
}

void handle_state_play(Context ctx) {}
void handle_state_endRound(Context ctx) {}
void handle_state_endGame(Context ctx) {}
