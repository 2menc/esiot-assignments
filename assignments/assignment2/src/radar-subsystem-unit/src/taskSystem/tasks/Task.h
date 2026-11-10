#ifndef __TASK__
#define __TASK__

/**
 * Base class of every periodic task run by the scheduler.
 * Subclasses implement init() and tick(); update() calls tick()
 * only when the task period has elapsed.
 */
class Task {
protected:
  int period;                  /**< task period in ms */

private:
  unsigned long lastTickTime;  /**< time of the last tick, in ms */

public:
  /**
   * Creates a task with the given period.
   * @param period task period in ms
   */
  Task(int period);

  virtual ~Task() {}

  /** Initialises the task; called once before the scheduler starts. */
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
