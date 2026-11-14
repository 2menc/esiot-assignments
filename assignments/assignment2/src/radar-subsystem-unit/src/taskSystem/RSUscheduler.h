#ifndef __RSU_SCHEDULER__
#define __RSU_SCHEDULER__

#include "tasks/Task.h"
#include "model/config.h"

/**
 * Cooperative scheduler of the Radar Subsystem Unit.
 * Holds the registered tasks and lets each one run when its period expires.
 */
class RSUscheduler {
private:
  Task* tickables[MAX_TASKS];  /**< registered tasks */
  int numTasks;                /**< number of registered tasks */

  /** Updates every registered task with the current time. */
  void tickAll();

public:
  RSUscheduler();

  /**
   * Adds a task to the scheduler.
   * @param task task to register
   * @return false if the scheduler is full
   */
  bool registerTask(Task* task);

  /** Runs one scheduling round; to be called in loop(). */
  void run();
};

#endif
