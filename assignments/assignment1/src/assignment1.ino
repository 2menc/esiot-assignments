#include "kernel.h"
#include "core.h"
#include "input.h"

void setup() {
  kernel_init();
  core_init();

  input_init(currentContext.players);

  change_state(STATE_WAITING_FOR_PLAYERS);
}

void loop() {  
  handle_current_state(currentContext);
}
