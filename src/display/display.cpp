
#include "display/display.hpp"
#include "images/boot_normal_img.hpp"
#include "images/boot_evil_img.hpp"
#include "images/image_manager.cpp"

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPIFFS.h>
#include "display_driver.hpp"

static DisplayState current_state = DISPLAY_IDLE;

void drawBootImage(DisplayState state) {
    const char* filename_jpg = (state == DISPLAY_IDLE) ? "/boot_idle.jpg" : "/boot_evil.jpg";
    const char* filename_png = (state == DISPLAY_IDLE) ? "/boot_idle.png" : "/boot_evil.png";

    if (SD.begin()) {
        if (SD.exists(filename_jpg)) {
            File f = SD.open(filename_jpg);
            if (f) {
                tft.drawJpg(&f, 0, 0, tft.width(), tft.height(), 0, 0, JPEG_DIV_NONE);
                f.close();
                return;
            }
        }
        if (SD.exists(filename_png)) {
            File f = SD.open(filename_png);
            if (f) {
                tft.drawPng(&f, 0, 0, tft.width(), tft.height(), 0, 0, 1.0f, 1.0f);
                f.close();
                return;
            }
        }
    }

    if (SPIFFS.begin(true)) {
        if (SPIFFS.exists(filename_jpg)) {
            File f = SPIFFS.open(filename_jpg);
            if (f) {
                tft.drawJpg(&f, 0, 0, tft.width(), tft.height(), 0, 0, JPEG_DIV_NONE);
                f.close();
                return;
            }
        }
        if (SPIFFS.exists(filename_png)) {
            File f = SPIFFS.open(filename_png);
            if (f) {
                tft.drawPng(&f, 0, 0, tft.width(), tft.height(), 0, 0, 1.0f, 1.0f);
                f.close();
                return;
            }
        }
    }

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
