#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

/** A sensor measuring the ambient temperature. */
class TemperatureSensor {
public:
  virtual ~TemperatureSensor() {}

  /** @return the temperature in °C */
  virtual float getTemperature() = 0;
};

#endif
