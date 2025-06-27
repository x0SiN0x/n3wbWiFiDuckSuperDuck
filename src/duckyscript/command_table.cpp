// Maps commands to opcodes
#include "parser.hpp"

// Normalize a line and return corresponding opcode
DuckyOpcode getOpcodeForLine(const String& line) {
    String cmd = line;
    int spaceIdx = cmd.indexOf(' ');
    if (spaceIdx > 0) {
        cmd = cmd.substring(0, spaceIdx);
    }

    cmd.toUpperCase();

    if (cmd == "REM") return OP_REM;
    if (cmd == "STRING") return OP_STRING;
    if (cmd == "DELAY") return OP_DELAY;

    return OP_UNKNOWN;
}
