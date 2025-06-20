#include "duckyscript/DuckyRuntime.h"

void DuckyRuntime::setCommands(const std::vector<DuckyCommand>& cmds) {
  commands = cmds;
  currentIndex = 0;
  conditionalPass = true;
  ifStack.clear();
}

bool DuckyRuntime::hasNext() {
  return currentIndex < commands.size();
}

const DuckyCommand& DuckyRuntime::next() {
  if (currentIndex < commands.size()) {
    const DuckyCommand& cmd = commands[currentIndex++];
    if (cmd.keyword != "REPEAT") lastCommand = cmd;
    return cmd;
  }
  return lastCommand;
}

void DuckyRuntime::repeatLast(int times) {
  for (int i = 0; i < times; ++i) {
    commands.insert(commands.begin() + currentIndex, lastCommand);
  }
}

void DuckyRuntime::setWatchdog(int ms) {
  watchdogMs = ms;
  lastFeed = millis();
}

void DuckyRuntime::feedWatchdog() {
  if (watchdogMs > 0 && (millis() - lastFeed) > watchdogMs) {
    ESP.restart();
  }
}

void DuckyRuntime::evalIf(const String& condition) {
  bool pass = condition == "TRUE"; // simple placeholder logic
  conditionalPass = pass;
  ifStack.push_back(pass);
}

void DuckyRuntime::evalElse() {
  if (!ifStack.empty()) {
    conditionalPass = !ifStack.back();
  }
}

void DuckyRuntime::evalEndIf() {
  if (!ifStack.empty()) {
    ifStack.pop_back();
    conditionalPass = ifStack.empty() ? true : ifStack.back();
  }
}
