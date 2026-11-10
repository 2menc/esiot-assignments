#ifndef __LED__
#define __LED__

#include "../Light.h"

/** A LED connected to a digital pin. */
class Led : public Light {
private:
  short pin;  /**< digital output pin */

public:
  /**
   * Creates the LED and configures its pin as output.
   * @param pin digital output pin
   */
  Led(short pin);

  void turnOn() override;
  void turnOff() override;
};

#endif
