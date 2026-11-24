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
   * Rotates the servo to the given angle, attaching it again if it was stopped.
   * @param angle target angle, from 0 to 180 degrees
   */
  void moveTo(int angle);

  /** @return the last commanded angle, in degrees */
  int getCurrentAngle();

  /**
   * Detaches the servo: the motor stops drawing current and no longer holds its position.
   * Used while the sonar measures, because the servo current disturbs the 5V line.
   */
  void stop();
};

#endif
