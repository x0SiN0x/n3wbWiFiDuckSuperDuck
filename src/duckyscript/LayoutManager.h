#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include <Arduino.h>

class LayoutManager {
public:
  LayoutManager();
  void setLayout(const String& name);
  String translate(const String& input);

private:
  String layout;
};

#endif
