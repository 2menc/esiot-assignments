#include "CommandParser.h"

#define PREFIX_CMD "cmd:"
#define PREFIX_ANGLE "value:"

Command CommandParser::parseCommand(const String& msg) {
  Command cmd = {CommandType::NONE, -1};

  // defensive copy
  String text = msg;
  text.trim();

  if(!text.startsWith(PREFIX_CMD)) {
    // it is not a cmd message
    return cmd;
  }

  // from : to : (or \0 if it is an angle command)
  const String body = text.substring(strlen(PREFIX_CMD));

  if(body == "TAKE") {
    cmd.type = CommandType::TAKE;
  } else if(body == "RELEASE") {
    cmd.type = CommandType::RELEASE;
  } else if(body == "RESET") {
    cmd.type = CommandType::RESET;
  } else if(body.startsWith(PREFIX_ANGLE)) {
    const String arg = body.substring(strlen(PREFIX_ANGLE));
    
    if(this->isAngleValid(arg)) { cmd.value = arg.toInt(); }
  }

  return cmd;
}

bool CommandParser::isAngleValid(const String &text) {
  
  // true if it could be an angle 0 <= a <= 180
  if(text.length() == 0 || text.length() < 3) { return false; }

  for(unsigned int i = 0; i < text.length(); i++) {
    if(!isDigit(text[i])) { return false; }
  }

  return text.toInt() <= 180 && text.toInt() >= 0;
}