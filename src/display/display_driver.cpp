
#include <Arduino.h>
#include "LGFX_Config.hpp"

LGFX tft;

void drawRGB565Image(const uint16_t *img, int width, int height) {
    tft.startWrite();
    tft.setAddrWindow(0, 0, width, height);
    tft.pushImage(0, 0, width, height, img);
    tft.endWrite();
}
