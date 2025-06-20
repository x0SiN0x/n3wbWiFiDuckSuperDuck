#ifndef DUCKY_COMMAND_H
#define DUCKY_COMMAND_H

#include <Arduino.h>

class DuckyCommand {
public:
  String keyword;
  String args;
  String raw;

  DuckyCommand(const String& line);
};

#endif
