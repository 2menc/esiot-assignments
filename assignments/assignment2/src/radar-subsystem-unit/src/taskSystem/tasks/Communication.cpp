#include "Communication.h"

/** State names sent on the serial line, in the same order as the State java enum. */
static const char* const STATE_NAMES[] = {"IDLE", "WORKING", "PRE_ALARM", "ALARM"};

Communication::Communication(unsigned int period, MessageChannel* channel, CommandParser* parser)
    : Task(period), channel(channel), parser(parser),
      lastCommand({CommandType::NONE, -1}), commandAvailable(false),
      pendingState(State::IDLE), stateToSend(false),
      pendingMeasure({false, 0, -1}), measureToSend(false) {
}

void Communication::init() {
  this->commandAvailable = false;
  this->stateToSend = false;
  this->measureToSend = false;
}

void Communication::tick() {
  this->transmit();
  this->receive();
}

void Communication::transmit() {
  if (this->stateToSend) {
    this->channel->sendMessage(String("state:") + STATE_NAMES[static_cast<int>(this->pendingState)]);
    this->stateToSend = false;
  }
  if (this->measureToSend) {
    String msg = "sector:";
    msg += this->pendingMeasure.sector + 1;        // the spec numbers sectors from 1
    msg += this->pendingMeasure.detected ? ":1:" : ":0:";
    msg += this->pendingMeasure.detected ? this->pendingMeasure.distance : -1;
    this->channel->sendMessage(msg);
    this->measureToSend = false;
  }
}

void Communication::receive() {
  const String msg = this->channel->receiveMessage();
  if (msg.length() == 0) {
    return;                                        // not complete yet
  }
  const Command cmd = this->parser->parseCommand(msg);
  if (cmd.type != CommandType::NONE) {             // ignore unknown messages
    this->lastCommand = cmd;
    this->commandAvailable = true;
  }
}

void Communication::sendStateToCSU(State state) {
  this->pendingState = state;
  this->stateToSend = true;
}

void Communication::sendSectorToCSU(Measure measure) {
  this->pendingMeasure = measure;
  this->measureToSend = true;
}

bool Communication::hasCommand() {
  return this->commandAvailable;
}

Command Communication::getCommand() {
  this->commandAvailable = false;                  // consumed
  return this->lastCommand;
}

void Communication::discardCommand() {
  this->commandAvailable = false;
}