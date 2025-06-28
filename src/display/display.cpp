
#include "display.hpp"
#include "images/boot_normal_img.hpp"
#include "images/boot_evil_img.hpp"
#include <Arduino.h>

extern void drawRGB565Image(const uint16_t *img, int width, int height);

static DisplayState current_state = DISPLAY_IDLE;

void updateDisplay(DisplayState state) {
    current_state = state;

    switch (state) {
        case DISPLAY_IDLE:
            drawRGB565Image(boot_normal_img, BOOT_NORMAL_IMG_WIDTH, BOOT_NORMAL_IMG_HEIGHT);
            break;
        case DISPLAY_ACTIVE:
            drawRGB565Image(boot_evil_img, BOOT_EVIL_IMG_WIDTH, BOOT_EVIL_IMG_HEIGHT);
            break;
    }
}

void showIdleScreen() {
    updateDisplay(DISPLAY_IDLE);
}

void showActiveScreen() {
    updateDisplay(DISPLAY_ACTIVE);
}
