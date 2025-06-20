#include "hid/HIDBackend.h"
#include "hid/MouseControl.h"

void MouseControl::move(const String& args) {
  int dx = 0, dy = 0;
  sscanf(args.c_str(), "%d %d", &dx, &dy);
  sendMouseMove(dx, dy);
}

void MouseControl::click(const String& args) {
  String type = args;
  type.trim();
  if (type == "LEFT") sendMouseClick(1);
  else if (type == "RIGHT") sendMouseClick(2);
  else if (type == "MIDDLE") sendMouseClick(4);
}

void MouseControl::jitter(int amount) {
  for (int i = 0; i < 5; ++i) {
    sendMouseMove(amount, 0);
    delay(10);
    sendMouseMove(-amount, 0);
    delay(10);
  }
}
