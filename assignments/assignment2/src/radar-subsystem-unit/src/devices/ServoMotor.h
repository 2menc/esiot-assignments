#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Arduino.h>
#include <Servo.h>

/** Servo motor that rotates the radar over 0..180 degrees. */
class ServoMotor {
private:
  short pin;         /**< control pin */
  int currentAngle;  /**< last commanded angle, in degrees */
  Servo servo;       /**< underlying Arduino servo driver */

public:
  /**
   * Creates the servo and attaches it to the given pin.
   * @param pin control pin
   */
  ServoMotor(short pin);

  /**
   * Rotates the servo to the given angle.
   * @param angle target angle, from 0 to 180 degrees
   */
  void moveTo(int angle);

  /** @return the last commanded angle, in degrees */
  int getCurrentAngle();

  /** Detaches the servo, so it no longer holds its position. */
  void stop();
};

#endif
