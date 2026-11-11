#ifndef __COMMUNICATION__
#define __COMMUNICATION__

#include "Task.h"
#include "SystemTypes.h"
#include "communication/MessageChannel.h"
#include "communication/CommandParser.h"

/**
 * Task exchanging data with the console.
 * Decides what to send and when, and turns incoming messages into commands.
 */
class Communication : public Task {
private:
  MessageChannel* channel;  /**< channel to the console */
  CommandParser* parser;    /**< translates messages into commands */

  Command lastCommand;      /**< last command received, not yet consumed */
  bool commandAvailable;    /**< true if lastCommand has not been read yet */

public:
  /**
   * Creates the task.
   * @param period task period in ms
   * @param channel channel to the console
   * @param parser command parser
   */
  Communication(unsigned int period, MessageChannel* channel, CommandParser* parser);

  void init() override;
  void tick() override;

  /**
   * Sends the current system state to the console.
   * @param state current system state
   */
  void sendStateToCSU(State state);

  /**
   * Sends the result of a sector measure to the console.
   * @param measure measure to send
   */
  void sendSectorToCSU(Measure measure);

  /** @return true if a command has been received and not read yet */
  bool hasCommand();

  /**
   * Returns the last command and marks it as read.
   * @return the last command received
   */
  Command getCommand();
};

#endif
