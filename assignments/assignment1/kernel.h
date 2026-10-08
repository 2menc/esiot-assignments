/*
  the kernel should manage gameState changes that can be caused by events or conditions
*/
#ifndef __KERNEL__
#define __KERNEL__

#include "Arduino.h" 
#include "core.h"

/* init should initialize the necessary structures to store players and context data*/
void kernel_init(); // no free: not necesary because of the gameloop

void change_state(State newState);
State get_current_state();
long get_current_time_in_state();
long get_entered_state_time();
bool is_just_entered_in_state();

void LOG(const String& messageAddress);

// context, players declatation
extern Context currentContext;
extern Player[NUMBER_OF_PLAYERS];

#endif