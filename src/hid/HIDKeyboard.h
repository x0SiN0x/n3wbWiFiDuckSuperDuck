#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <Arduino.h>
#include "Keyboard.h"

class HIDKeyboard {
public:
  void type(const String& text);
  void pressAndRelease(uint8_t key, const String& mod = "");
  void sendCombo(const String& key, const String& mod);
};

#endif
