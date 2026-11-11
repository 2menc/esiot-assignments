#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

#define SOUND_SPEED 331.45f // ms^-1
#define SOUND_SPEED_TEMPERATURE_FACTOR 0.62f

#define ECHO_TIMEOUT_MICROS 20000   // ~3.4 m range, within the 50 ms task period

#define MICROS_IN_A_SECOND 1000000.0f

#include "../DistanceSensor.h"


/** HC-SR04 sonar: measures distance from the echo time of an ultrasonic pulse. */
class UltrasonicSensor : public DistanceSensor {
private:
  short triggerPin;  /**< pin sending the pulse */
  short echoPin;     /**< pin receiving the echo */

  /** Sends a 10 us pulse on the trigger pin to start a measure. */
  void sendEcho();

public:
  /**
   * Creates the sensor and configures its pins.
   * @param triggerPin pin sending the pulse
   * @param echoPin pin receiving the echo
   */
  UltrasonicSensor(short triggerPin, short echoPin);

  int getDistance(float temperature) override;  // overrides the DistanceSensor method
};

#endif
