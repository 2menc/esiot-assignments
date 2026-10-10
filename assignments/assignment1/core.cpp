#include "core.h"
#include "kernel.h"
#include "input.h"
#include <avr/sleep.h>
#include "view.h"

#define DEFAULT_BAUD_RATE 9600
#define FADE_FREQUENCY 25  //ms

short lastWinPlayer = -1;
uint8_t roundCounter;

unsigned int current_T1 = 10000;
unsigned int calculate_random_time(unsigned int previousTime);
void fault(Player &player);
void reset_presses(Context &ctx);
void score_increase(Player &player);
uint16_t calculate_next_T1(uint16_t previous_T1, uint8_t roundCounter);

void handle_current_state(Context &currentContext) {

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
void handle_state_waitingForPlayers(Context &ctx) {
  /*
  all green leds should be off and all red led should be pulsing 
  (fading in and out, when R1 is fading in, R2 should be fading out), 
  waiting for players to start the game;
  */

  //LOG("WAITING FOR PLAYERS");

  static short currentFade[2] = { 0, 255 };
  static short fadeStep[2] = { 5, -5 };

  roundCounter = 0;

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

  // LCD
  short cursor[2] = { 0, 0 };
  display(MESSAGE_WAITING, cursor, DISPLAY_ROLLING);


  // wait for both buttons
  bool allPressed = true;
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if (!is_button_pressed(i)) {
      allPressed = false;
      break;
    }
  }
  if(allPressed) {
    change_state(STATE_PLAY);
  }

  // checks if time ran out
  if (get_current_time_in_state() >= WAITING_TIMEOUT) {
    input_reset();
    change_state(STATE_SLEEP);
    return;
  }
}

void handle_state_sleep(Context ctx) {

  short cursorCenterSleep[2] = {LCD_WIDTH/2 - 2, 0};

  display("SLEEP", cursorCenterSleep, DISPLAY_STATIC);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  //first thing: wake
  sleep_disable();

  short cursorCenterWake[2] = {LCD_WIDTH/2 - 3, 0};

  display("WOKE UP", cursorCenterWake, DISPLAY_STATIC);
  delay(700);
  change_state(STATE_WAITING_FOR_PLAYERS);
}

static unsigned long T1 = 10000;           
static bool numberShown = false;
static unsigned long phaseStartTime = 0;
static unsigned long randomWaitTime = 0;
static uint8_t currentNumber = 0;
void handle_state_play(Context &ctx) {

  short cursorCenter[2] = {LCD_WIDTH/2 -1, 0};

  /*
    the leds are turned off and the LCD gets cleared. 
  */
  if (just_entered_state()) {
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
      led_turn_off(ctx.players[i].redLedPin);
      led_turn_off(ctx.players[i].greenLedPin);
    }
    roundCounter = 0;
    display(MESSAGE_GO, cursorCenter, DISPLAY_STATIC);
    delay(1000);
    lcd_clear();
    input_reset();

    numberShown = false;
    phaseStartTime = millis();

    randomWaitTime = random(1000, WAITING_TIMEOUT);
    T1 = calculate_next_T1(current_T1, roundCounter);
    currentNumber = get_random_number();

    return;
  }

  /*
    checks for fault
  */
  if (!numberShown) {

    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
      if (is_button_pressed(i)) {
        fault(ctx.players[i]);

        change_state(STATE_END_ROUND);

        return;
      }
    }  

  /*
    After a random amt. of time 0 < t < MAX_WAIT ms, the number is shown;
  */
  if (millis() - phaseStartTime >= randomWaitTime) {
      numberShown = true;
      phaseStartTime = millis(); 

      input_reset();

      LOG("current T1 :" + String(current_T1));
      display(String(currentNumber), cursorCenter, DISPLAY_INFORMATIONS);
    }
    return;
  }

  /*
    checks times pressed
  */
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if(is_button_pressed(i)) {
      button_clear(i);

      ctx.players[i].timesPressed++;

      if(ctx.players[i].timesPressed == currentNumber) {
        
        lastWinPlayer = i;
        change_state(STATE_END_ROUND);
        return;
      }
    }
  }

  /*
    wait for players
  */
  if (millis() - phaseStartTime > T1) {
    change_state(STATE_END_GAME);
    return;
  }
}

void handle_state_endRound(Context &ctx) {
  reset_presses(ctx);

  if (lastWinPlayer >= 0) {            
    short winner = lastWinPlayer;
    lastWinPlayer = -1;
    score_increase(ctx.players[winner]);

    String scores = "P1:" + String(ctx.players[0].score) + " P2:" + String(ctx.players[1].score);
    short cursor[2] = {LCD_WIDTH/2 - (scores.length() / 2), 1};
    display(scores, cursor, DISPLAY_STATIC);

    led_turn_on(ctx.players[winner].greenLedPin);
    delay(2000);
    led_turn_off(ctx.players[winner].greenLedPin);
  }

  change_state(STATE_PLAY);
}

void handle_state_endGame(Context &ctx) {
  if (just_entered_state()) LOG("GAME OVER");   
}


uint16_t calculate_next_T1(uint16_t previous_T1, uint8_t roundCounter) {

  float divisionFactor = 1.1 + (get_difficulty() * roundCounter);
  unsigned long new_T1 = previous_T1 / divisionFactor;

  if (new_T1 < 300) {
      new_T1 = 300; 
  }

  return new_T1;
}

uint8_t get_random_number() {
  return (random() % MAX_NUMBER) + 1;
}

void fault(Player &player) {

  led_turn_on(player.redLedPin);
  
  if(player.score > 0) {
    player.score--;
  } else {
    change_state(STATE_END_GAME);
  }
  
  delay(2000);

  led_turn_off(player.redLedPin);
}

void reset_presses(Context &ctx) {
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    ctx.players[i].timesPressed = 0;
  }
}

/*
  automatically increases the score of player(s) who won
*/
/*
short search_winner(Context ctx) {
  short best = 0;

  // searches the best score
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if(ctx.players[i].score >= best) {
      best = ctx.players[i].score;
    }
  }


  // increases player's score
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if(ctx.players[i].score == best) {
      return i;
    }
  }
}
*/

void score_increase(Player &player) {
  player.score++;
}






