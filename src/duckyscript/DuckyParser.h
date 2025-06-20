#ifndef DUCKY_PARSER_H
#define DUCKY_PARSER_H

#include <Arduino.h>
#include <vector>
#include "DuckyCommand.h"

class DuckyParser {
public:
  void parse(const String& script);
  const std::vector<DuckyCommand>& getCommands() const;

private:
  std::vector<DuckyCommand> commands;
};

#endif
