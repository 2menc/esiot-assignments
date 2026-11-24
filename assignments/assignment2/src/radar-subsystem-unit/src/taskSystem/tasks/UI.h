#ifndef __UI__
#define __UI__

#include "Task.h"
#include "devices/Light.h"
#include "devices/Screen.h"
#include "../../model/config.h"

/** States of the alarm LED FSM. */
enum class LedState {
  ALARM_LED_ON,
  ALARM_LED_OFF
};

/**
 * Task driving the local user interface: ON and ALARM LEDs and the LCD.
 * Outside IDLE the ON LED is lit and the LCD shows the last measured sector.
 * The ALARM LED is steady in PRE_ALARM and blinks in ALARM.
 */
class UI : public Task {
private:
  Screen* lcd;                  /**< display for sector and distance */
  Light* redLed;                /**< ALARM LED */
  Light* greenLed;              /**< ON LED */

  LedState blinkState;          /**< current state of the ALARM LED */
  unsigned long lastBlinkTime;  /**< time of the last ALARM LED toggle, in ms */
  State state;                  /**< system state to display */
  int sector;                   /**< last measured sector, from 0 */
  int distance;                 /**< last measured distance, in cm */
  bool detected;                /**< true if an object was found in the last sector */
  bool stateChanged;            /**< true if the state changed since the last tick */
  bool measureChanged;          /**< true if a new measure arrived since the last tick */

  /** @return true if the ALARM LED has kept its state for LED_BLINK_PERIOD */
  bool blinkTicksPassed();

  /** Writes sector and distance on the display. */
  void showInfo();

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
   * Sets the measure to display.
   * @param measure last measure taken by the radar
   */
  void setMeasure(Measure measure);

  /**
   * Sets the system state to display.
   * @param newState current system state
   */
  void setState(State newState);
};

#endif
