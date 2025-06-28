#include "layout_manager.hpp"

static String currentLayout = "US";

void LayoutManager::setLayout(const String &layout) {
  currentLayout = layout;
}

String LayoutManager::getCurrentLayout() {
  return currentLayout;
}

LayoutManager layout_manager;
