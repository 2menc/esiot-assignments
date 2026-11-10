#ifndef __SYSTEM_TYPES__
#define __SYSTEM_TYPES__

#include "config.h"

/** States of the Radar Subsystem Unit, shared by tasks and console protocol. */
enum State {
  IDLE,
  WORKING,
  PRE_ALARM,
  ALARM
};

/** Who drives the radar position: the scan (auto), the operator (manual) or nobody. */
enum ControlMode {
  AUTO,
  MANUAL,
  NONE
};

/** Result of a sonar reading on a single sector. */
typedef struct Measure {
  bool detected;  /**< true if an object was found in the sector */
  int sector;     /**< sector index, from 0 to NUM_SECTORS - 1 */
  int distance;   /**< object distance in cm, meaningful only if detected */
} Measure;

#endif
