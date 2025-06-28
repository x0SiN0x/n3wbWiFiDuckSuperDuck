
#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "display/LGFX_Config.hpp"

void setup() {
  Serial.begin(115200);
  extern LGFX tft;
  tft.init();
  tft.setBrightness(255);
  tft.fillScreen(TFT_RED); // TEMP: test panel response
  delay(1000);
}

void loop() {
  // your loop logic
}
