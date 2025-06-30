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

inline DuckyScriptVersion currentVersion = VERSION_V1;
inline DuckyOpcode getOpcodeForLine(const String& line) {
    String cmd = line;
    int idx = cmd.indexOf(' ');
    if (idx > 0) cmd = cmd.substring(0, idx);
    cmd.toUpperCase();
    if (cmd == "DEFAULT_DELAY") return OP_DEFAULT_DELAY;
    if (cmd == "DEFAULT_CHAR_DELAY") return OP_DEFAULT_CHAR_DELAY;
    if (cmd == "KEY_PRESS_DELAY") return OP_KEY_PRESS_DELAY;
    if (cmd == "STRING") return OP_STRING;
    if (cmd == "STRINGLN" || cmd == "ENTER") return OP_STRINGLN;
    if (cmd == "LOAD_PNG") return OP_LOAD_PNG;
    if (cmd == "LOAD_JPG") return OP_LOAD_JPG;
    if (cmd == "IF" || cmd == "ENDIF") return OP_REM;
    return OP_UNKNOWN;
}

inline Instruction parseLine(const String& line) {
    if (line.startsWith("REM v3+")) { currentVersion = VERSION_V3PLUS; return {OP_REM, ""}; }
    else if (line.startsWith("REM v3")) { currentVersion = VERSION_V3; return {OP_REM, ""}; }
    else if (line.startsWith("REM v2")) { currentVersion = VERSION_V2; return {OP_REM, ""}; }

    DuckyOpcode op = getOpcodeForLine(line);
    String arg = "";
    int sp = line.indexOf(' ');
    if (sp > 0) arg = line.substring(sp + 1);
    return {op, arg};
}

struct ParseResult {
    bool success;
    String error;
};

class DuckyParser {
public:
    inline ParseResult parse(const String& script) {
        ParseResult result{true, ""};
        int start = 0;
        while (start <= script.length()) {
            int end = script.indexOf('\n', start);
            String line = (end == -1) ? script.substring(start) : script.substring(start, end);
            line.trim();
            if (!line.isEmpty()) {
                Instruction instr = parseLine(line);
                if (instr.opcode == OP_UNKNOWN) {
                    result.success = false;
                    result.error = String("Unknown command: ") + line;
                    break;
                }
            }
            if (end == -1) break;
            start = end + 1;
        }
        return result;
    }
    ParseResult parse(const std::string& script) {
        return parse(String(script.c_str()));
    }
};
