
#include "display_driver.hpp"

LGFX tft;

void initDisplay() {
    tft.init();
    tft.setBrightness(255);
    clearDisplay();
}

void setDisplayBrightness(uint8_t level) {
    tft.setBrightness(level);
}

void clearDisplay(uint16_t color) {
    tft.fillScreen(color);
}

void drawRGB565Image(const uint16_t *img, int width, int height) {
    tft.startWrite();
    tft.setAddrWindow(0, 0, width, height);
    tft.pushImage(0, 0, width, height, img);
    tft.endWrite();
}
