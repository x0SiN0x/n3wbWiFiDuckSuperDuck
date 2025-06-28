
#include "display.hpp"
#include "images/n3wb_main_img.hpp"
#include "images/n3wb_main_evil_img.hpp"
#include <Arduino.h>

// Placeholder for the actual draw function connected to TFT
extern void drawRGB565Image(const uint16_t *img, int width, int height);

enum DisplayState {
    DISPLAY_IDLE,
    DISPLAY_ACTIVE
};

static DisplayState current_state = DISPLAY_IDLE;

void updateDisplay(DisplayState state) {
    current_state = state;

    switch (state) {
        case DISPLAY_IDLE:
            drawRGB565Image(n3wb_main_img, N3WB_MAIN_IMG_WIDTH, N3WB_MAIN_IMG_HEIGHT);
            break;
        case DISPLAY_ACTIVE:
            drawRGB565Image(n3wb_main_evil_img, N3WB_MAIN_EVIL_IMG_WIDTH, N3WB_MAIN_EVIL_IMG_HEIGHT);
            break;
    }
}

void showIdleScreen() {
    updateDisplay(DISPLAY_IDLE);
}

void showActiveScreen() {
    updateDisplay(DISPLAY_ACTIVE);
}
