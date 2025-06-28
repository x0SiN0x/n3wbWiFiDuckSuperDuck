
#include "display/display.hpp"
#include "images/boot_normal_img.hpp"
#include "images/boot_evil_img.hpp"

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPIFFS.h>

extern LGFX tft;

static DisplayState current_state = DISPLAY_IDLE;

void drawBootImage(DisplayState state) {
    const char* filename_jpg = (state == DISPLAY_IDLE) ? "/boot_idle.jpg" : "/boot_evil.jpg";
    const char* filename_png = (state == DISPLAY_IDLE) ? "/boot_idle.png" : "/boot_evil.png";

    if (SD.begin() && SD.exists(filename_jpg)) {
        tft.drawJpgFile(SD, filename_jpg, 0, 0);
        return;
    }
    if (SD.exists(filename_png)) {
        tft.drawPngFile(SD, filename_png, 0, 0);
        return;
    }
    if (SPIFFS.begin(true) && SPIFFS.exists(filename_jpg)) {
        tft.drawJpgFile(SPIFFS, filename_jpg, 0, 0);
        return;
    }
    if (SPIFFS.exists(filename_png)) {
        tft.drawPngFile(SPIFFS, filename_png, 0, 0);
        return;
    }

    // fallback to embedded
    if (state == DISPLAY_IDLE) {
        tft.drawPng(boot_normal_img, boot_normal_img_len, 0, 0);
    } else {
        tft.drawPng(boot_evil_img, boot_evil_img_len, 0, 0);
    }
}

void updateDisplay(DisplayState state) {
    current_state = state;
    drawBootImage(state);
}

void showIdleScreen() {
    updateDisplay(DISPLAY_IDLE);
}

void showActiveScreen() {
    updateDisplay(DISPLAY_ACTIVE);
}
