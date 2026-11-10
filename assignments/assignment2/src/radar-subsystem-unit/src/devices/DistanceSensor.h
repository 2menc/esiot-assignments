#ifndef __DISTANCE_SENSOR__
#define __DISTANCE_SENSOR__

/** A sensor measuring the distance of the nearest object. */
class DistanceSensor {
public:
  virtual ~DistanceSensor() {}

  /**
   * Measures the distance of the nearest object.
   * @param temperature air temperature in °C, used to calibrate the measure
   * @return distance in cm, or a negative value if no object is detected
   */
  virtual int getDistance(float temperature) = 0;
};

#endif
