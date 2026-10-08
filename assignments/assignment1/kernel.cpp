#include "kernel.h"
#include "config.h"
#include "core.h"

Context currentContext;

/* init should initialize the necessary structures to store players and context data*/
void kernel_init() {
  for(int i = 0; i < NUMBER_OF_PLAYERS; i++) {

  }
}

void change_state(State newState);
State get_current_state();
long get_current_time_in_state();
long get_entered_state_time();
bool is_just_entered_in_state();

void LOG(const String& messageAddress);


//helpers

Player player_create(short playerNumber) {
  Player player;


}