#include "SerialChannel.h"

SerialChannel::SerialChannel(unsigned long baudRate) : baudRate(baudRate), inputBuffer("") {
  Serial.begin(baudRate);
}

void SerialChannel::sendMessage(const String& msg) {
  Serial.println(msg);
}

String SerialChannel::receiveMessage() {
  while(Serial.available() > 0) {
    const char c =(char) Serial.read();
    if(c == '\n' || c == '\0') {
      String msg = this->inputBuffer;
      this->inputBuffer = "";
      msg.trim();
      return msg;
    }
    this->inputBuffer += c;

    if(this->inputBuffer.length() > MAX_MSG_LENGTH) { 
      this->inputBuffer = ""; 
    }
  } 

  return "";
}
