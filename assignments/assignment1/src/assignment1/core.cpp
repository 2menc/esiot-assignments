#include "core.h"
#include "kernel.h"
#include "input.h"
#include <avr/sleep.h>
#include "view.h"

#define DEFAULT_BAUD_RATE 9600
#define FADE_FREQUENCY 25  //ms

#define T1_START 5000
#define T1_MIN 600  

short lastWinPlayer = -1;
uint8_t roundCounter;

void fault(Context &ctx, short playerIndex);
void reset_presses(Context &ctx);
void score_increase(Player &player);
uint16_t calculate_next_T1(uint16_t previous_T1, uint8_t roundCounter);
void show_scores(Context &ctx);
short search_winner(Context &ctx);

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

void handle_state_sleep(Context &ctx) {

  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    led_turn_off(ctx.players[i].redLedPin);
  }

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
static long reachedAt[NUMBER_OF_PLAYERS];   
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
    roundCounter++;
    display(MESSAGE_GO, cursorCenter, DISPLAY_STATIC);
    delay(1000);
    lcd_clear();
    input_reset();

    numberShown = false;
    phaseStartTime = millis();

    randomWaitTime = random(1000, MAX_WAIT);
    T1 = (roundCounter == 1) ? T1_START : calculate_next_T1(T1, roundCounter);
    currentNumber = get_random_number();

    // resets player response times
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) reachedAt[i] = -1;
    return;
  }

  /*
    checks for fault
  */
  if (!numberShown) {
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
      if (is_button_pressed(i)) {
        fault(ctx, i);

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

      LOG("current T1 :" + String(T1));
      display(String(currentNumber), cursorCenter, DISPLAY_INFORMATIONS);
    }
    return;
  }

  /*
    manages buttons
  */
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    if(is_button_pressed(i)) {
      button_clear(i);

      ctx.players[i].timesPressed++;

      if(ctx.players[i].timesPressed == currentNumber && reachedAt[i] == -1) {
        reachedAt[i] = millis();
      }
    }
  }

  /*
    T1 passed
  */
  if (millis() - phaseStartTime > T1) {
    short winner = -1;
    bool someoneFaulted = false;

    for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
      if (ctx.players[i].timesPressed > currentNumber) {
        someoneFaulted = true;
        fault(ctx, i);
      // player i reached the number && (noone won || the current player was faster than the (current) winner)  
      } else if(reachedAt[i] >= 0 && (winner < 0 || reachedAt[i] < reachedAt[winner])) { 
        // then he is the new winner
        winner = i;
      }
    }
             
    if (winner < 0 && !someoneFaulted) {  // if no player reached or outcame the specified value
      change_state(STATE_END_GAME);                           
    } else {
      lastWinPlayer = winner;     // there is not a wimnner                   
      change_state(STATE_END_ROUND);
    }
    return;    
  }
}

void handle_state_endRound(Context &ctx) {
  reset_presses(ctx);

  if (lastWinPlayer >= 0) {            
    short winner = lastWinPlayer;
    lastWinPlayer = -1;
    score_increase(ctx.players[winner]);

    show_scores(ctx);

    led_turn_on(ctx.players[winner].greenLedPin);
    delay(2000);
    led_turn_off(ctx.players[winner].greenLedPin);
  }

  change_state(STATE_PLAY);
}

void handle_state_endGame(Context &ctx) {
  if (just_entered_state()) {

    short winner = search_winner(ctx);

    lcd_clear();
    unsigned long startTime = millis();
    while(millis() - startTime <= 10000) {
      if(winner == -1) {
        //short cursorCenterTie[2] = {LCD_WIDTH/2 - (MESSAGE_TIE.length()/2), 0};
        display(MESSAGE_TIE, NULL, DISPLAY_ROLLING);
      } else {
        //short cursorCenterWin[2] = {LCD_WIDTH/2 - (MESSAGE_WINNER.length()/2), 0};
        display(MESSAGE_WINNER + "P" + String(ctx.players[winner].playerNumber) , NULL, DISPLAY_ROLLING);
      }
    }
  } 

  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) ctx.players[i].score = 0;
  input_reset();

  change_state(STATE_WAITING_FOR_PLAYERS);
}

void show_scores(Context &ctx) {
  String scores = "P1:" + String(ctx.players[0].score) + " P2:" + String(ctx.players[1].score);
  short cursor[2] = { LCD_WIDTH/2 - (short)(scores.length() / 2), 1 };
  display(scores, cursor, DISPLAY_STATIC);
}

uint16_t calculate_next_T1(uint16_t previous_T1, uint8_t roundCounter) {

  float divisionFactor = 1.05 + 0.05 * get_difficulty();  
  unsigned long new_T1 = previous_T1 / divisionFactor;

  return (new_T1 < T1_MIN) ? T1_MIN : new_T1;
}

uint8_t get_random_number() {
  return (random() % MAX_NUMBER) + 1;
}

void fault(Context &ctx, short playerIndex) {

  led_turn_on(ctx.players[playerIndex].redLedPin);
  

  if(ctx.players[playerIndex].score > 0) {
    ctx.players[playerIndex].score--;
  } else {
    change_state(STATE_END_GAME);
  }
  
  show_scores(ctx);

  delay(2000);

  led_turn_off(ctx.players[playerIndex].redLedPin);
}

void reset_presses(Context &ctx) {
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    ctx.players[i].timesPressed = 0;
  }
}

/*
  -1 = tie
*/
short search_winner(Context &ctx) {   
  short best = ctx.players[0].score;
  short winner = 0;
  bool tie = false;

  for (int i = 1; i < NUMBER_OF_PLAYERS; i++) {
    if (ctx.players[i].score > best) {
      best = ctx.players[i].score;
      winner = i;
      tie = false;
    } else if (ctx.players[i].score == best) {
      tie = true;
    }
  }
  return tie ? -1 : winner;
}


void score_increase(Player &player) {
  player.score++;
}






