#ifndef __COMMUNICATION__
#define __COMMUNICATION__

#include "Task.h"
#include "../../model/config.h"
#include "communication/MessageChannel.h"
#include "communication/CommandParser.h"

/**
 * Task exchanging data with the console.
 * Sends the pending state and measure, and turns incoming messages into commands.
 */
class Communication : public Task {
private:
  MessageChannel* channel;  /**< channel to the console */
  CommandParser* parser;    /**< translates messages into commands */

  Command lastCommand;      /**< last command received, not yet consumed */
  bool commandAvailable;    /**< true if lastCommand has not been read yet */

  State pendingState;       /**< state to send at the next tick */
  bool stateToSend;         /**< true if pendingState has not been sent yet */
  Measure pendingMeasure;   /**< measure to send at the next tick */
  bool measureToSend;       /**< true if pendingMeasure has not been sent yet */

  /** Sends the pending state and measure, if any. */
  void transmit();

  /** Reads a message from the console and stores it if it is a valid command. */
  void receive();

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
   * Schedules the current system state to be sent to the console.
   * @param state current system state
   */
  void sendStateToCSU(State state);

  /**
   * Schedules a sector measure to be sent to the console.
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

  /** Drops any command received but not read yet. */
  void discardCommand();
};

#endif