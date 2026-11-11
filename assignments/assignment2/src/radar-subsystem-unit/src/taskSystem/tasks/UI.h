#ifndef __UI__
#define __UI__

#include "Task.h"
#include "../SystemTypes.h"
#include "../../devices/Light.h"
#include "../../devices/Screen.h"

/** States of the alarm LED FSM. */
enum class LedState {
  ALARM_LED_ON,
  ALARM_LED_OFF
};

/**
 * Task driving the local user interface: ON and ALARM LEDs and the LCD.
 * Shows the current state and the last measured sector.
 */
class UI : public Task {
private:
  Screen* lcd;          /**< display for sector and distance */
  Light* redLed;        /**< ALARM LED */
  Light* greenLed;      /**< ON LED */

  LedState blinkState;  /**< current state of the ALARM LED */
  int blinkTicks;       /**< ticks elapsed since the last ALARM LED toggle */
  State state;          /**< system state to display */
  int sector;           /**< last measured sector */
  int distance;         /**< last measured distance, in cm */

  /**
   * Toggles a LED when the blink period has elapsed.
   * @param led LED to blink
   */
  void blink(Light* led);

public:
  /**
   * Creates the task.
   * @param period task period in ms
   * @param lcd display
   * @param redLed ALARM LED
   * @param greenLed ON LED
   */
  UI(unsigned int period, Screen* lcd, Light* redLed, Light* greenLed);

  void init() override;
  void tick() override;

  /**
   * Sets the system state to display.
   * @param state current system state
   */
  void setState(State state);

  /**
   * Sets the measure to display.
   * @param measure last measure taken by the radar
   */
  void setMeasure(Measure measure);
};

#endif
