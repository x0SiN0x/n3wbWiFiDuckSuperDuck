#ifndef DUCKY_RUNTIME_H
#define DUCKY_RUNTIME_H

#include <vector>
#include "DuckyCommand.h"

class DuckyRuntime {
public:
  void setCommands(const std::vector<DuckyCommand>& cmds);
  bool hasNext();
  const DuckyCommand& next();
  void repeatLast(int times);
  void setWatchdog(int ms);
  void feedWatchdog();
  void evalIf(const String& condition);
  void evalElse();
  void evalEndIf();

private:
  std::vector<DuckyCommand> commands;
  size_t currentIndex = 0;
  DuckyCommand lastCommand;
  int watchdogMs = 0;
  unsigned long lastFeed = 0;
  bool conditionalPass = true;
  std::vector<bool> ifStack;
};

#endif
