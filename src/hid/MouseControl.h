#ifndef MOUSE_CONTROL_H
#define MOUSE_CONTROL_H

#include <Arduino.h>
#include "Mouse.h"

class MouseControl {
public:
  void move(const String& args);
  void click(const String& args);
  void jitter(int amount);
};

#endif
