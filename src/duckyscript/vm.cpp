// VM executor for parsed DuckyScript instructions
#include "parser.hpp"
#include "vm.hpp"
#include <Arduino.h>

// Execute one instruction
void executeInstruction(const Instruction& instr) {
    switch (instr.opcode) {
        case OP_REM:
            // Comments are ignored
            break;

        case OP_STRING:
            Serial.print("Typing: ");
            Serial.println(instr.argument);
            // TODO: send HID keypresses
            break;

        case OP_DELAY:
            Serial.print("Delay: ");
            Serial.println(instr.argument.toInt());
            delay(instr.argument.toInt());
            break;

        default:
            Serial.println("Unknown instruction.");
            break;
    }
}
