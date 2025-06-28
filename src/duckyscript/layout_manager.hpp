#pragma once
#include <Arduino.h>

class LayoutManager {
public:
  void setLayout(const String& layout);
  String getCurrentLayout();
};

extern LayoutManager layout_manager;
