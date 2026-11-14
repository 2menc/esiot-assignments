#ifndef __MESSAGE_CHANNEL__
#define __MESSAGE_CHANNEL__

#include <Arduino.h>

/** A channel exchanging text messages, one per line, with the console. */
class MessageChannel {
public:
  virtual ~MessageChannel() {}

  /**
   * Sends a message.
   * @param msg message to send, without the line terminator
   */
  virtual void sendMessage(const String& msg) = 0;

  /**
   * Returns the last complete message and removes it from the channel.
   * @return the received message, without the line terminator
   */
  virtual String receiveMessage() = 0;
};

#endif
