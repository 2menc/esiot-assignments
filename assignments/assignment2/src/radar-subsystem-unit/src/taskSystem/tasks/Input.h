#ifndef __INPUT__
#define __INPUT__

#include "Task.h"
#include "../../devices/Button.h"
#include "../../devices/AngleSensor.h"
#include "../../devices/TemperatureSensor.h"
#include "config.h"

/** Number of buttons handled by the Input task. */
#define NUM_BUTTONS 3

/** Button clicks detected by the Input task. */
enum class ButtonEvent {
  NONE,
  START,
  STOP,
  RESET
};

/**
 * Task sampling the physical inputs: buttons, potentiometer and temperature.
 * Turns button presses into click events for the Controller.
 */
class Input : public Task {
private:
  Button* buttons[NUM_BUTTONS];    /**< START, STOP and RESET buttons, in this order */
  AngleSensor* pot;                /**< potentiometer for manual control */
  TemperatureSensor* tempSensor;   /**< sensor used to calibrate the sonar */

  bool lastButtons[NUM_BUTTONS];   /**< button states at the previous tick, for click detection */
  ButtonEvent lastEvent;           /**< last click detected, not yet consumed */
  int potAngle;                    /**< last sampled potentiometer angle */
  float temperature;               /**< last sampled temperature */

public:
  /**
   * Creates the task.
   * @param period task period in ms
   * @param start START button
   * @param stop STOP button
   * @param reset RESET button
   * @param pot potentiometer
   * @param tempSensor temperature sensor
   */
  Input(unsigned int period, Button* start, Button* stop, Button* reset,
        AngleSensor* pot, TemperatureSensor* tempSensor);

  void init() override;
  void tick() override;

  /** @return the last sampled temperature, in °C */
  float getTemperature();

  /**
   * Returns the last click and consumes it, so each click is read once.
   * @return the clicked button, or NONE
   */
  ButtonEvent getButtonEvent();

  /** @return the last sampled potentiometer angle, from 0 to 180 degrees */
  int getPotAngle();
};

#endif
