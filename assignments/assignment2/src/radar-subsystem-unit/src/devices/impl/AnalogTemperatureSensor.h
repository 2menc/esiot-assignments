#ifndef __ANALOG_TEMPERATURE_SENSOR__
#define __ANALOG_TEMPERATURE_SENSOR__

#include "../TemperatureSensor.h"

/** Analog temperature sensor (TMP36 or LM35) on an analog pin. */
class AnalogTemperatureSensor : public TemperatureSensor {
private:
  short pin;  /**< analog input pin */

  /**
   * Converts the sensor output voltage to a temperature.
   * @param V voltage in volts
   * @return temperature in °C
   */
  float convertVtoTemp(float V);

public:
  /**
   * Creates the sensor on the given pin.
   * @param pin analog input pin
   */
  AnalogTemperatureSensor(short pin);

  float getTemperature() override;
};

#endif
