#include "parser.hpp"
#include "vm.hpp"
#include "../usb/usb_composite.hpp"
#include "../display/image_loader.hpp"

extern LGFX tft;

bool attack_hid = true;
bool attack_storage = true;

void executeInstruction(const Instruction& instr) {
    if (instr.opcode == OP_ATTACKMODE) {
        String mode = instr.argument;
        mode.toUpperCase();

        attack_hid = mode.indexOf("HID") >= 0;
        attack_storage = mode.indexOf("STORAGE") >= 0;

        Serial.print("ATTACKMODE set: ");
        Serial.print(attack_hid ? "HID " : "");
        Serial.print(attack_storage ? "STORAGE " : "");
        Serial.println();

        usb_init_composite(attack_hid, attack_storage);
        return;
    }

    if (instr.opcode == OP_RUN) {
        draw_image(tft, "/n3wb_main_evil.png");
    }

    if (instr.opcode == OP_END) {
        draw_image(tft, "/n3wb_main.png");
    }
}
