// Script runner: reads a script line by line, parses, and executes
#include "runner.hpp"
#include "parser.hpp"
#include "vm.hpp"

#include <Arduino.h>

void runScript(Stream& stream) {
    String line;
    Instruction lastInstruction = { OP_UNKNOWN, "" };

    while (stream.available()) {
        line = stream.readStringUntil('\n');
        line.trim();

        if (line.isEmpty()) continue;

        Instruction instr = parseLine(line);

        if (instr.opcode == OP_REPEAT) {
            int count = instr.argument.toInt();
            for (int i = 0; i < count; ++i) {
                executeInstruction(lastInstruction);
            }
        } else {
            executeInstruction(instr);
            lastInstruction = instr;
        }
    }
}
