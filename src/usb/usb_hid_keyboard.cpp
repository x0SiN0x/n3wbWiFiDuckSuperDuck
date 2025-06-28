
#include <Arduino.h>
#include "usb_hid_keyboard.hpp"
#include "tusb.h"

void sendKey(uint8_t keycode) {
    uint8_t keycodes[6] = { 0 };
    keycodes[0] = keycode;
    tud_hid_keyboard_report(0, 0, keycodes);
    delay(5);
    tud_hid_keyboard_report(0, 0, NULL);  // release key
}
