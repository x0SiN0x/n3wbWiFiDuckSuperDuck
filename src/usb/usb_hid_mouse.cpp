
#include <Arduino.h>
#include "usb_hid_mouse.hpp"
#include "tusb.h"

void moveMouse(int x, int y, int wheel) {
    tud_hid_mouse_report(0, 0, x, y, wheel);
}
