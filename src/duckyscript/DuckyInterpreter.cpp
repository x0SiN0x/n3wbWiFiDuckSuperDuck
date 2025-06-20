#include "duckyscript/DuckyInterpreter.h"

extern bool ENABLE_DEBUG;

DuckyInterpreter::DuckyInterpreter() {}

void DuckyInterpreter::loadScript(const String& script) {
  parser.parse(script);
  runtime.setCommands(parser.getCommands());
}

void DuckyInterpreter::setAttackMode(bool hid, bool storage) {
  enableHID = hid;
  enableStorage = storage;
  if (ENABLE_DEBUG) {
    Serial.printf("[Ducky] ATTACKMODE: HID=%d, STORAGE=%d\n", hid, storage);
  }
}

void DuckyInterpreter::run() {
  while (runtime.hasNext()) {
    const DuckyCommand& cmd = runtime.next();
    if (ENABLE_DEBUG) {
      Serial.printf("[Ducky] Executing: %s\n", cmd.raw.c_str());
    }
    executeCommand(cmd);
  }
}

void DuckyInterpreter::executeCommand(const DuckyCommand& cmd) {
  String keyword = cmd.keyword;

  if (keyword == "STRING") {
    keyboard.type(cmd.args);
  } else if (keyword == "DELAY") {
    delayWithWatchdog(cmd.args.toInt());
  } else if (keyword == "ENTER") {
    keyboard.pressAndRelease(KEY_ENTER);
  } else if (keyword == "GUI" || keyword == "WINDOWS") {
    keyboard.pressAndRelease(KEY_LEFT_GUI, cmd.args);
  } else if (keyword == "REM") {
    return; // Comment line
  } else if (keyword == "REPEAT") {
    runtime.repeatLast(cmd.args.toInt());
  } else if (keyword == "JITTER") {
    mouse.jitter(cmd.args.toInt());
  } else if (keyword == "WATCHDOG") {
    runtime.setWatchdog(cmd.args.toInt());
  } else if (keyword == "MOUSEMOVE") {
    mouse.move(cmd.args);
  } else if (keyword == "CLICK") {
    mouse.click(cmd.args);
  } else if (keyword == "MEDIA") {
    media.send(cmd.args);
  } else if (keyword == "IF") {
    runtime.evalIf(cmd.args);
  } else if (keyword == "ELSE") {
    runtime.evalElse();
  } else if (keyword == "ENDIF") {
    runtime.evalEndIf();
  } else {
    keyboard.sendCombo(keyword, cmd.args);
  }
}

void DuckyInterpreter::delayWithWatchdog(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    delay(10);
    runtime.feedWatchdog();
  }
}
