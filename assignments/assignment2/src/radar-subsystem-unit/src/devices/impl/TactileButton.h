#ifndef __TACTILE_BUTTON__
#define __TACTILE_BUTTON__

#include "../Button.h"

/** Minimum time the pin must stay still before a new press is accepted, in ms. */
#define DEBOUNCE_TIME 150

/** Maximum number of tactile buttons, one interrupt handler each. */
#define MAX_BUTTONS 3

/**
 * Tactile push button on a digital pin, read through a pin change interrupt.
 * Presses are debounced in the interrupt and stored until read with wasPressed().
 */
class TactileButton : public Button {
private:
  short pin;                          /**< digital input pin */
  volatile bool pressed;              /**< true if a press has not been read yet */
  volatile unsigned long lastChange;  /**< time of the last change on the pin, in ms */

  static TactileButton* instances[MAX_BUTTONS];  /**< buttons, indexed by handler */
  static int numInstances;                       /**< number of buttons created */

  /** Debounces a change on the pin and records a press on a clean rising edge. */
  void handleInterrupt();

  /** Interrupt handlers, one per button: they forward to handleInterrupt(). */
  static void handler0();
  static void handler1();
  static void handler2();

public:
  /**
   * Creates the button, configures its pin and enables its interrupt.
   * Must be created inside setup(), after the hardware is initialised.
   * @param pin digital input pin
   */
  TactileButton(short pin);

  bool wasPressed() override;
};

#endif
