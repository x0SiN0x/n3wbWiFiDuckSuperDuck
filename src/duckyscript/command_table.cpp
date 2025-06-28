extern bool display_overridden;
#include "parser.hpp"

DuckyOpcode getOpcodeForLine(const String& line) {
    String cmd = line;
    int spaceIdx = cmd.indexOf(' ');
    if (spaceIdx > 0) cmd = cmd.substring(0, spaceIdx);
    cmd.toUpperCase();

    if (cmd == "ATTACKMODE") return OP_ATTACKMODE;
    if (cmd == "REM") return OP_REM;
    if (cmd == "STRING") return OP_STRING;
    if (cmd == "STRINGLN") return OP_STRINGLN;
    if (cmd == "DELAY") return OP_DELAY;
    if (cmd == "DEFAULT_DELAY") return OP_DEFAULT_DELAY;
    if (cmd == "DEFAULT_CHAR_DELAY") return OP_DEFAULT_CHAR_DELAY;
    if (cmd == "KEY_PRESS_DELAY") return OP_KEY_PRESS_DELAY;
    if (cmd == "REPEAT") return OP_REPEAT;
    if (cmd == "LOAD_PNG") return OP_LOAD_PNG;
    if (cmd == "LOAD_JPG") return OP_LOAD_JPG;
    if (cmd == "WAIT_FOR_BUTTON_PRESS") return OP_WAIT_FOR_BUTTON_PRESS;
    if (cmd == "LED_OFF") return OP_LED_OFF;
    if (cmd == "LED_R") return OP_LED_R;
    if (cmd == "LED_G") return OP_LED_G;
    if (cmd == "LED_B") return OP_LED_B;
    if (cmd == "STOP_PAYLOAD") return OP_STOP_PAYLOAD;
    if (cmd == "RESET") return OP_RESET;
    if (cmd == "SET_LAYOUT") return OP_SET_LAYOUT;

    return OP_UNKNOWN;
}
