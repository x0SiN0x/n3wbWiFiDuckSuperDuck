#pragma once
#include <Arduino.h>

enum DuckyScriptVersion {
    VERSION_V1,
    VERSION_V2,
    VERSION_V3,
    VERSION_V3PLUS
};

enum DuckyOpcode {
    OP_REM,
    OP_STRING,
    OP_DELAY,
    OP_UNKNOWN
};

// Parsed instruction structure
struct Instruction {
    DuckyOpcode opcode;
    String argument;
};

// Global script version (set per file)
extern DuckyScriptVersion currentVersion;

// Parse a single line into opcode + argument
Instruction parseLine(const String& line);
