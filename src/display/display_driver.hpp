
#pragma once
#include "LGFX_Config.hpp"  // defines LGFX

// Global TFT display instance
extern LGFX tft;

// Basic utilities
void initDisplay();
void setDisplayBrightness(uint8_t level);
void clearDisplay(uint16_t color = 0x0000);
void drawRGB565Image(const uint16_t *img, int width, int height);
