#include "Communication.h"

Communication::Communication(unsigned int period, MessageChannel* channel, CommandParser* parser)
    : Task(period), channel(channel), parser(parser),
      lastCommand({CommandType::NONE, 0}), commandAvailable(false) {
}

void Communication::init() {
}

void Communication::tick() {
}

void Communication::sendStateToCSU(State state) {
}

void Communication::sendSectorToCSU(Measure measure) {
}

bool Communication::hasCommand() {
  return commandAvailable;
}

Command Communication::getCommand() {
  return lastCommand;
}
