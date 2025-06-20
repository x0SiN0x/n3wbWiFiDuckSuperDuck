#include "duckyscript/DuckyCommand.h"

DuckyCommand::DuckyCommand(const String& line) {
  raw = line;
  int spaceIdx = line.indexOf(' ');
  if (spaceIdx == -1) {
    keyword = line;
    args = "";
  } else {
    keyword = line.substring(0, spaceIdx);
    args = line.substring(spaceIdx + 1);
  }
  keyword.trim();
  args.trim();
}
