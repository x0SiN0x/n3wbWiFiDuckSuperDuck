#pragma once

class LayoutManager {
public:
  void setLayout(const String &layout);
  String getCurrentLayout();
};

extern LayoutManager layout_manager;
