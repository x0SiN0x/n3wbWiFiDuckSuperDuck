#pragma once
#include <Arduino.h>

enum DuckyScriptVersion {
    VERSION_V1, VERSION_V2, VERSION_V3, VERSION_V3PLUS
};

enum DuckyOpcode {
    OP_REM, OP_STRING, OP_STRINGLN, OP_DELAY,
    OP_DEFAULT_DELAY, OP_DEFAULT_CHAR_DELAY, OP_KEY_PRESS_DELAY,
    OP_REPEAT, OP_LOAD_PNG, OP_LOAD_JPG, OP_WAIT_FOR_BUTTON_PRESS,
    OP_LED_OFF, OP_LED_R, OP_LED_G, OP_LED_B,
    OP_STOP_PAYLOAD, OP_RESET, OP_SET_LAYOUT,
    OP_ATTACKMODE, OP_UNKNOWN
};

struct Instruction {
    DuckyOpcode opcode;
    String argument;
};

extern DuckyScriptVersion currentVersion;
Instruction parseLine(const String& line);
