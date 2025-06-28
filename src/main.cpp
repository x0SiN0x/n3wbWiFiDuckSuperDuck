#include <Arduino.h>

#ifdef HAS_TFT
#include "display/display.hpp"
#include "display/LGFX_Config.hpp"
#endif

extern LGFX tft;

void setup() {
  Serial.begin(115200);

  // set up our Display if it exists
#ifdef HAS_TFT
  tft.begin();
  tft.setBrightness(255);
  showIdleScreen();
#endif

}

void loop() {
  // your loop logic
}
