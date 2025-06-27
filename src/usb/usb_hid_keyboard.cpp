// HID Keyboard stub
#include "tusb.h"

void send_hid_key(const char* text) {
    while (*text) {
        tud_hid_keyboard_report(0, 0, (const uint8_t[]){ *text });
        tud_task();
        delay(5);
        text++;
    }
}
