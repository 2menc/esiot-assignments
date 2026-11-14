#ifndef __COMMAND_PARSER__
#define __COMMAND_PARSER__

#include <Arduino.h>

/** Kinds of command the console can send. */
enum class CommandType {
  NONE,     /**< invalid or unknown message */
  TAKE,     /**< take remote control of the radar */
  RELEASE,  /**< release remote control */
  RESET,    /**< reset the system from the alarm state */
  ANGLE     /**< move the radar to the angle in value */
};

/** A command received from the console. */
typedef struct Command {
  CommandType type;  /**< type of command */
  int value;         /**< argument, used only by ANGLE */
} Command;

/** Translates a text message from the console into a Command. */
class CommandParser {
public:
  /** Prepares the parser. */
  void init();

  /**
   * Parses a message.
   * @param msg message received from the console
   * @return the decoded command, with type NONE if the message is not valid
   */
  Command parseCommand(const String& msg);
};

#endif
