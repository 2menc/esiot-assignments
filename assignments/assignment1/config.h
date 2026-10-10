#ifndef __CONFIG__
#define __CONFIG__

#define NUMBER_OF_PLAYERS 2

#define PIN_BUTTON_ONE 4
#define PIN_BUTTON_TWO 5

#define POTENTIOMETER_PIN 3 //pin that supports pwm

/*
 the config.cpp will automatically assign each player his pins, between 9 and 12. 
 Both buttons will be on pin 1 and 2, in order to send interrupts
*/
#define PIN_LED_GREEN_ONE 9
#define PIN_LED_RED_ONE 11  //pwm

#define PIN_LED_GREEN_TWO 12
#define PIN_LED_RED_TWO 10  //pwm

#include "core.h"

void assign_pins_to_player(Player &player);

#endif
