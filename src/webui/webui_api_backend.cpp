
#include "api_log.hpp"
#include "usb/usb_hid_keyboard.hpp"
#include "usb/usb_hid_mouse.hpp"
#include "webui_hid_bridge.hpp"
#include <Arduino.h>

void handleDummyAction() {
    Serial.println("[WebUI] Dummy HID action triggered");
    send_hid_key("ENTER");
    send_mouse_move(10, 10);
}
