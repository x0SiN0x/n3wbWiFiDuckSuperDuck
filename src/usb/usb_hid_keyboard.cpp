
#include <string>
#include "usb_hid_keyboard.hpp"

void injectString(const std::string& text) {
    for (char c : text) {
        if (c == '\n') {
            sendKey(HID_KEY_ENTER);
        } else {
            sendKey(c);
        }
        delay(5); // Respect default key delay
    }
}
