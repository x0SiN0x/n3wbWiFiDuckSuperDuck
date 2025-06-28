#include <Arduino.h>
#include "display/display.hpp"      // ✅ Fix: ensures showIdleScreen() is declared
#include "display/LGFX_Config.hpp"

extern LGFX tft;

void setup() {
  Serial.begin(115200);
  tft.begin();              // ✅ Preferred over tft.init() for full panel init
  tft.setBrightness(255);
  showIdleScreen();         // ✅ Show boot image
}

void loop() {
  // your loop logic
}
