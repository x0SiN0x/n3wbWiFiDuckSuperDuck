#include "hid/HIDKeyboard.h"

void HIDKeyboard::type(const String& text) {
  Keyboard.begin();
  for (size_t i = 0; i < text.length(); ++i) {
    Keyboard.print(text[i]);
  }
  Keyboard.end();
}

void HIDKeyboard::pressAndRelease(uint8_t key, const String& mod) {
  Keyboard.begin();
  if (mod == "CTRL") Keyboard.press(KEY_LEFT_CTRL);
  if (mod == "ALT") Keyboard.press(KEY_LEFT_ALT);
  if (mod == "SHIFT") Keyboard.press(KEY_LEFT_SHIFT);
  if (mod == "GUI") Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(key);
  delay(10);
  Keyboard.releaseAll();
  Keyboard.end();
}

void HIDKeyboard::sendCombo(const String& key, const String& mod) {
  // Basic support for keys like CTRL ALT DEL
  pressAndRelease(key[0], mod); // Simplified for demo purposes
}
