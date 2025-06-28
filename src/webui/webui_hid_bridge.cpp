
#include "webui_hid_bridge.hpp"
#include "usb/usb_hid_keyboard.hpp"
#include "usb/usb_hid_mouse.hpp"
#include "tusb.h"

void send_hid_key(const std::string& key) {
    if (key == "ENTER") sendKey(HID_KEY_ENTER);
    // extend key mappings as needed
}

void send_hid_string(const std::string& text) {
    for (char c : text) {
        sendKey(c);
    }
}

void send_mouse_move(int dx, int dy) {
    moveMouse(dx, dy, 0);
}
