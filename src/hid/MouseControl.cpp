#include "hid/MouseControl.h"

void MouseControl::move(const String& args) {
  int dx = 0, dy = 0;
  sscanf(args.c_str(), "%d %d", &dx, &dy);
  Mouse.begin();
  Mouse.move(dx, dy);
  Mouse.end();
}

void MouseControl::click(const String& args) {
  String type = args;
  type.trim();
  Mouse.begin();
  if (type == "LEFT") Mouse.click(MOUSE_LEFT);
  else if (type == "RIGHT") Mouse.click(MOUSE_RIGHT);
  else if (type == "MIDDLE") Mouse.click(MOUSE_MIDDLE);
  Mouse.end();
}

void MouseControl::jitter(int amount) {
  Mouse.begin();
  for (int i = 0; i < 5; ++i) {
    Mouse.move(amount, 0);
    delay(10);
    Mouse.move(-amount, 0);
    delay(10);
  }
  Mouse.end();
}
