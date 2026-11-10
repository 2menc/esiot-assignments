#include "SerialChannel.h"

SerialChannel::SerialChannel(unsigned long baudRate) : baudRate(baudRate), inputBuffer("") {
}

void SerialChannel::sendMessage(const String& msg) {
}

bool SerialChannel::isMessageAvailable() {
  return false;
}

String SerialChannel::receiveMessage() {
  return "";
}
