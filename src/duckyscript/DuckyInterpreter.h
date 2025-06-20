#ifndef DUCKY_INTERPRETER_H
#define DUCKY_INTERPRETER_H

#include <Arduino.h>
#include "DuckyCommand.h"
#include "DuckyParser.h"
#include "DuckyRuntime.h"
#include "LayoutManager.h"
#include "../hid/HIDKeyboard.h"
#include "../hid/MouseControl.h"
#include "../hid/MediaControl.h"

class DuckyInterpreter {
public:
  DuckyInterpreter();

  void loadScript(const String& script);
  void run();
  void setAttackMode(bool hid, bool storage);

private:
  DuckyParser parser;
  DuckyRuntime runtime;
  HIDKeyboard keyboard;
  MouseControl mouse;
  MediaControl media;
  LayoutManager layout;

  bool enableHID = true;
  bool enableStorage = false;

  void executeCommand(const DuckyCommand& cmd);
  void delayWithWatchdog(unsigned long ms);
};

#endif
