// Keyboard layout manager: handles dynamic layout switching
#include "layout_manager.hpp"
#include "keycodes.hpp"
#include <Arduino.h>
#include <map>

String currentLayout = "US";

// Simulated runtime layout switch
bool setKeyboardLayout(const String& layout) {
    String l = layout;
    l.toUpperCase();

    if (l == "US" || l == "UK" || l == "DE" || l == "FR") {
        currentLayout = l;
        Serial.print("Layout changed to: ");
        Serial.println(currentLayout);
        return true;
    }

    Serial.print("Unsupported layout: ");
    Serial.println(layout);
    return false;
}

String getKeyboardLayout() {
    return currentLayout;
}

LayoutManager layout_manager;


String LayoutManager::getCurrentLayout() {
    return currentLayout;
}

void LayoutManager::setLayout(const String& layout) {
    setKeyboardLayout(layout);
}
