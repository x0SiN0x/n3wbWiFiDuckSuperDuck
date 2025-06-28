#include <Arduino.h>
#include "usb_hid_keyboard.hpp"
#include "tusb.h"
#include <string>

void send_hid_key(const char* key) {
    uint8_t buf[6] = { 0 };
    buf[0] = *key;
    tud_hid_keyboard_report(0, 0, buf);
    delay(5);
    tud_hid_keyboard_report(0, 0, NULL);
}


void send_hid_string(const char* str) {
    for (char c : text) {
        if (c == '\n') {
            sendKey(KEY_ENTER);
        } else {
            sendKey(c);
        }
        delay(5); // Respect default key delay
    }
}
}

void injectString(const std::string& text) {
    for (char c : text) {
        if (c == '\n') {
            sendKey(KEY_ENTER);
        } else {
            sendKey(c);
        }
        delay(5); // Respect default key delay
    }
}
