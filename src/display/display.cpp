// Display control: handles idle/status image switching
#include "LGFX_Config.hpp"
#include "image_loader.hpp"

static LGFX tft;
static bool isPayloadRunning = false;

void display_init() {
    tft.init();
    tft.setRotation(1);
    display_idle();
}

void display_idle() {
    isPayloadRunning = false;
    draw_image(tft, "/n3wb_main.png");
}

void display_payload_active() {
    isPayloadRunning = true;
    draw_image(tft, "/n3wb_main_evil.png");
}
