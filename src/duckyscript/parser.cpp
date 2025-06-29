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

ParseResult DuckyParser::parse(const std::string& script) {
    ParseResult result{true, ""};
    String src(script.c_str());
    int idx = 0;
    while (idx < src.length()) {
        int newline = src.indexOf('\n', idx);
        if (newline < 0) newline = src.length();
        String line = src.substring(idx, newline);
        line.trim();
        if (!line.isEmpty()) {
            Instruction instr = parseLine(line);
            if (instr.opcode == OP_UNKNOWN) {
                result.success = false;
                result.error = String("Unknown command: ") + line;
                break;
            }
        }
        idx = newline + 1;
    }
    return result;
}
