#include "kernel.h"
#include "core.h"
#include "input.h"

Context ctx;

void setup() {
  kernel_init();
  core_init();

  ctx = get_current_context();

  input_init(ctx.players);

  change_state(STATE_WAITING_FOR_PLAYERS);
}

void loop() {
  ctx = get_current_context();
  
  handle_current_state(ctx);
}
