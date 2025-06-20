#include "duckyscript/LayoutManager.h"

LayoutManager::LayoutManager() {
  layout = "us"; // default
}

void LayoutManager::setLayout(const String& name) {
  layout = name;
}

String LayoutManager::translate(const String& input) {
  // For now, return as-is (stub)
  return input;
}
