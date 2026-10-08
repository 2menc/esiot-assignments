#ifndef __INPUT__
#define __INPUT__

#include "config.h"

extern bool buttonsPressed[NUMBER_OF_PLAYERS];
extern long lastPressedTimes[NUMBER_OF_PLAYERS];

void input_init();
bool is_button_pressed(short buttonIndex);
void input_reset();

void button_handler(short index);

#endif