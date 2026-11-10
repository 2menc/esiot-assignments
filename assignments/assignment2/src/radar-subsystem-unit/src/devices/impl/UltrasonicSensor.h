#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

#include "../DistanceSensor.h"

/** HC-SR04 sonar: measures distance from the echo time of an ultrasonic pulse. */
class UltrasonicSensor : public DistanceSensor {
private:
  short triggerPin;  /**< pin sending the pulse */
  short echoPin;     /**< pin receiving the echo */

  /** Sends a 10 us pulse on the trigger pin. */
  void sendEcho();

  /**
   * Waits for the echo, with a timeout so the task period is not exceeded.
   * @return echo duration in us, or 0 if no echo arrived
   */
  long readEchoTime();

public:
  /**
   * Creates the sensor and configures its pins.
   * @param triggerPin pin sending the pulse
   * @param echoPin pin receiving the echo
   */
  UltrasonicSensor(short triggerPin, short echoPin);

  int getDistance(float temperature) override;
};

#endif
