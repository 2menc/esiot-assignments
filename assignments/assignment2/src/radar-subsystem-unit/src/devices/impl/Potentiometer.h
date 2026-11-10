#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "../AngleSensor.h"

/** Potentiometer on an analog pin, read as an angle for manual radar control. */
class Potentiometer : public AngleSensor {
private:
  short pin;  /**< analog input pin */

  /**
   * Maps the voltage read on the pin to an angle.
   * @param V voltage in volts, from 0 to 5
   * @return angle from 0 to 180 degrees
   */
  int convertVToAngle(float V);

public:
  /**
   * Creates the potentiometer on the given pin.
   * @param pin analog input pin
   */
  Potentiometer(short pin);

  int getAngle() override;
};

#endif
