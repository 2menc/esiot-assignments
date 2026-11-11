#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "Task.h"
#include "SystemTypes.h"
#include "Input.h"
#include "Radar.h"
#include "UI.h"
#include "Communication.h"

/**
 * Main task of the system: implements the IDLE / WORKING / PRE_ALARM / ALARM FSM.
 * Reads inputs and console commands, drives the radar and informs UI and console.
 */
class Controller : public Task {
private:
  Input* input;                  /**< source of clicks, pot angle and temperature */
  Radar* radar;                  /**< radar to drive */
  UI* ui;                        /**< local user interface */
  Communication* communication;  /**< link to the console */

  State currentState;            /**< current FSM state */
  int dists[NUM_SECTORS];        /**< last distance per sector, negative if no object */
  int currentSpeed;              /**< scan speed sent to the radar */
  ControlMode controlMode;       /**< control mode sent to the radar */
  bool remote;                   /**< true if the console has taken control in ALARM */
  int potAngle;                  /**< last potentiometer angle */
  int targetAngle;               /**< angle sent to the radar in MANUAL mode */
  float temperature;             /**< last temperature, forwarded to the radar */
  int remoteAngle;               /**< last angle requested by the console */

  /**
   * Computes the minimum distance over all sectors with an object.
   * @return the minimum distance in cm, or a negative value if no object is detected
   */
  int getCurrentMinDistance();

  /** Puts the MCU in deep sleep until START is pressed. */
  void sleep();

public:
  /**
   * Creates the task.
   * @param period task period in ms
   * @param input Input task
   * @param radar Radar task
   * @param ui UI task
   * @param communication Communication task
   */
  Controller(unsigned int period, Input* input, Radar* radar, UI* ui, Communication* communication);

  void init() override;
  void tick() override;
};

#endif
