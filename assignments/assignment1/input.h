#ifndef __INPUT__
#define __INPUT__

#include "config.h"

extern bool buttonsPressed[NUMBER_OF_PLAYERS];
extern long lastPressedTimes[NUMBER_OF_PLAYERS];

void input_init(Player players[NUMBER_OF_PLAYERS]);
bool is_button_pressed(short buttonIndex);
void input_reset();

void button_handler(short index);
short get_difficulty();

#endif