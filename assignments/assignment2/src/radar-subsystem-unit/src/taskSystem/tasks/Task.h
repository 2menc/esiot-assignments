#ifndef __TASK__
#define __TASK__

/**
 * Base class of every periodic task run by the scheduler.
 * Subclasses implement init() and tick(); update() calls tick()
 * only when the task period has elapsed.
 * 
 * ! IMPORTANT: the initialization should begin after all instantiations to avoid
 * ! problems related to non-existing yet objects.
 * 
 * ! IMPORTANT: values like temperature, potentiometer angle, .. should to be sampled
 * ! at the task period pace: these values get stored in variables, rather than being
 * ! measured in real time, violating the period time
 */
class Task {
protected:
  unsigned int period;                  /**< task period in ms */

private:
  unsigned long lastTickTime;  /**< time of the last tick, in ms */

public:
  /**
   * Creates a task with the given period.
   * @param period task period in ms
   */
  Task(unsigned int period);

  virtual ~Task() {}

  /** Initialises the task; called once before the scheduler starts. 
  */
  virtual void init() = 0;

  /** Executes one step of the task FSM. */
  virtual void tick() = 0;

  /**
   * Calls tick() if at least one period has passed since the last tick.
   * @param now current time in ms
   */
  void update(unsigned long now);
};

#endif
