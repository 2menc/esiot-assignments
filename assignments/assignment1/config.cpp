#include "config.h"

short maxTotalPins = NUMBER_OF_PLAYERS * (2 + 1);

void assign_pins_to_player(Player &player) {
  #ifdef __CORE__

  switch(player.playerNumber) {
    case 1: {
      player.buttonPin = PIN_BUTTON_ONE;
      player.greenLedPin = PIN_LED_GREEN_ONE;
      player.redLedPin = PIN_LED_RED_ONE;
    }
    case 2: {
      player.buttonPin = PIN_BUTTON_TWO;
      player.greenLedPin = PIN_LED_GREEN_TWO;
      player.redLedPin = PIN_LED_RED_TWO;
    }
    default: return;
  }

  #endif
}

