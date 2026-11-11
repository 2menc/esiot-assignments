#ifndef __RADAR__
#define __RADAR__

#include "Task.h"
#include "SystemTypes.h"
#include "devices/DistanceSensor.h"
#include "devices/ServoMotor.h"

/** States of the Radar task FSM. */
enum class RadarState {
  STOPPED,
  MOVING,
  MEASURING,
  MANUAL
};

/**
 * Task moving the sonar over the sectors and measuring each one.
 * In AUTO mode it scans forward and backward, in MANUAL mode it follows
 * the target angle, in NONE mode it stays still.
 */
class Radar : public Task {
private:
  DistanceSensor* sonar;     /**< sensor measuring the distance */
  ServoMotor* servo;         /**< motor rotating the sonar */

  RadarState state;          /**< current FSM state */
  int sector;                /**< current sector, from 0 to NUM_SECTORS - 1 */
  short dir;                   /**< scan direction: +1 forward, -1 backward */
  int ticks;                 /**< ticks spent in the current state */
  ControlMode controlMode;   /**< mode set by the Controller */
  float temperature;         /**< temperature used to calibrate the sonar */
  int currentSpeed;          /**< scan speed: ticks to wait on each sector */
  int targetAngle;           /**< angle to reach in MANUAL mode */
  Measure lastMeasure;       /**< last completed measure */
  bool newMeasure;           /**< true if lastMeasure has not been read yet */

  /**
   * Converts a sector index to the servo angle at its centre.
   * @param sector sector index
   * @return angle in degrees
   */
  int convertSectorToAngle(int sector);

  /**
   * changes state
   */
  void changeState(RadarState state);

  void enterMeasuring();
  void enterMoving();

public:
  /**
   * Creates the task.
   * @param period task period in ms
   * @param sonar distance sensor
   * @param servo servo motor
   */
  Radar(unsigned int period, DistanceSensor* sonar, ServoMotor* servo);

  void init() override;
  void tick() override;

  /**
   * Sets who drives the radar position.
   * @param mode AUTO, MANUAL or NONE
   */
  void setControlMode(ControlMode mode);

  /**
   * Sets the scan speed.
   * @param speed ticks to wait on each sector
   */
  void setSpeed(int speed);

  /**
   * Sets the temperature used to calibrate the sonar.
   * @param temperature temperature in °C
   */
  void setTemperature(float temperature);

  /**
   * Sets the angle to reach in MANUAL mode.
   * @param angle angle from 0 to 180 degrees
   */
  void setTargetAngle(int angle);

  /** @return true if a measure is ready and has not been read yet */
  bool hasNewMeasure();

  /**
   * Returns the last measure and marks it as read.
   * @return the last measure
   */
  Measure getMeasure();
};

#endif
