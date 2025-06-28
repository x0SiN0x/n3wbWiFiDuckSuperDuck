
#pragma once

enum DisplayState {
    DISPLAY_IDLE,
    DISPLAY_ACTIVE
};

void updateDisplay(DisplayState state);
void showIdleScreen();
void showActiveScreen();
