#ifndef __SERIAL_CHANNEL__
#define __SERIAL_CHANNEL__

#include <Arduino.h>
#include "../MessageChannel.h"

#define MAX_MSG_LENGTH 15

/** Message channel over the USB serial line. */
class SerialChannel : public MessageChannel {
private:
  unsigned long baudRate;  /**< serial speed in bit/s */
  String inputBuffer;  /**< characters received so far for the next message */

public:
  /**
   * Opens the serial line.
   * @param baudRate serial speed in bit/s
   */
  SerialChannel(unsigned long baudRate);

  void sendMessage(const String& msg) override;
  String receiveMessage() override;
};

#endif
