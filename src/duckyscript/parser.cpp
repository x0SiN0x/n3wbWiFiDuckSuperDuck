// DuckyScript parser implementation
// Supports v1, v2, v3, and custom v3+ syntax

#include "parser.hpp"
#include "command_table.hpp"

DuckyScriptVersion currentVersion = VERSION_V1;

Instruction parseLine(const String& line) {
    if (line.startsWith("REM v3+")) {
        currentVersion = VERSION_V3PLUS;
        return { OP_REM, "" };
    } else if (line.startsWith("REM v3")) {
        currentVersion = VERSION_V3;
        return { OP_REM, "" };
    } else if (line.startsWith("REM v2")) {
        currentVersion = VERSION_V2;
        return { OP_REM, "" };
    }

    DuckyOpcode op = getOpcodeForLine(line);
    String arg = "";

    int spaceIdx = line.indexOf(' ');
    if (spaceIdx > 0) {
        arg = line.substring(spaceIdx + 1);
    }

    return { op, arg };
}
