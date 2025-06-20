#include "duckyscript/DuckyParser.h"

void DuckyParser::parse(const String& script) {
  commands.clear();
  int start = 0;
  while (true) {
    int end = script.indexOf('\n', start);
    String line = (end == -1) ? script.substring(start) : script.substring(start, end);
    line.trim();
    if (line.length() > 0) {
      commands.emplace_back(line);
    }
    if (end == -1) break;
    start = end + 1;
  }
}

const std::vector<DuckyCommand>& DuckyParser::getCommands() const {
  return commands;
}
