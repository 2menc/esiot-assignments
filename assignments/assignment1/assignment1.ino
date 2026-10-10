#include "kernel.h"
#include "core.h"

void setup() {
  // put your setup code here, to run once:
  kernel_init();
  change_state(STATE_WAITING_FOR_PLAYERS);
}

void loop() {
  // put your main code here, to run repeatedly:
}
