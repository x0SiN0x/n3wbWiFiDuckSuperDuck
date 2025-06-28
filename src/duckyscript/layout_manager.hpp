#pragma once
#include <Arduino.h>

bool setKeyboardLayout(const String& layout);
String getKeyboardLayout();

extern LayoutManager layout_manager;
