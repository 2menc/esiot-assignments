#ifndef __TACTILE_BUTTON__
#define __TACTILE_BUTTON__

#define DEBOUNCE_TIME 150 // ms

#include "../Button.h"

/** Tactile push button on a digital pin. */
class TactileButton : public Button {
private:
  short pin;  /**< digital input pin */

  unsigned long lastTimePressed;

public:
  /**
   * Creates the button and configures its pin as input.
   * @param pin digital input pin
   */
  TactileButton(short pin);

  bool isPressed() override;
};

#endif
