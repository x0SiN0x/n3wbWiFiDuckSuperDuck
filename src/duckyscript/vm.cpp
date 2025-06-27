#include "parser.hpp"
#include "vm.hpp"
#include <Arduino.h>

// Runtime delay configuration
int defaultDelayMs = 0;
int keyPressDelayMs = 5;
int defaultCharDelayMs = 0;

void executeInstruction(const Instruction& instr) {
    switch (instr.opcode) {
        case OP_REM:
            // Ignore comment
            break;

        case OP_STRING:
            Serial.print("Typing: ");
            for (char c : instr.argument) {
                Serial.print(c);
                delay(defaultCharDelayMs);
            }
            Serial.println();
            break;

        case OP_STRINGLN:
            Serial.print("Typing + Enter: ");
            Serial.println(instr.argument);
            // Append ENTER press here
            break;

        case OP_DELAY:
            delay(instr.argument.toInt());
            break;

        case OP_DEFAULT_DELAY:
            defaultDelayMs = instr.argument.toInt();
            break;

        case OP_DEFAULT_CHAR_DELAY:
            defaultCharDelayMs = instr.argument.toInt();
            break;

        case OP_KEY_PRESS_DELAY:
            keyPressDelayMs = instr.argument.toInt();
            break;

        case OP_REPEAT:
            Serial.print("Repeat: not implemented in VM yet
");
            break;

        case OP_LOAD_PNG:
        case OP_LOAD_JPG:
            Serial.printf("Display image: %s
", instr.argument.c_str());
            break;

        case OP_WAIT_FOR_BUTTON_PRESS:
            Serial.println("Waiting for button (stub)...");
            break;

        case OP_LED_OFF:
        case OP_LED_R:
        case OP_LED_G:
        case OP_LED_B:
            Serial.printf("LED control command: %d
", instr.opcode);
            break;

        case OP_STOP_PAYLOAD:
            Serial.println("Payload stopped.");
            break;

        case OP_RESET:
            Serial.println("Rebooting...");
            ESP.restart();
            break;

        default:
            Serial.println("Unknown instruction.");
            break;
    }

    if (defaultDelayMs > 0 && instr.opcode != OP_DELAY) {
        delay(defaultDelayMs);
    }
}
