/*
  the kernel should manage gameState changes that can be caused by events or conditions
*/
#ifndef __KERNEL__
#define __KERNEL__

#include "Arduino.h" 
#include "core.h"
#include "config.h"

extern Context currentContext;

/* init should initialize the necessary structures to store players and context data*/
void kernel_init(); // no free: not necesary because of the gameloop

void change_state(State newState);
Context get_current_context();
long get_current_time_in_state();
long get_entered_state_time();

void LOG(const String& messageAddress);

// context, players declatation
extern Context currentContext;
extern Player players[NUMBER_OF_PLAYERS];


void led_fade(short ledPin, int &currentPulseValue, short fadeAmount);
void led_turn_off(short ledPin);


#endif