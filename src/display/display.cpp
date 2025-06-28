#include "LGFX_Config.hpp"
#include "image_loader.hpp"

extern LGFX tft;

void display_idle();
void display_payload_active();

void display_init() {
    tft.init();
    tft.setRotation(1);
    display_idle();
}

void display_idle() {
    draw_image(tft, "/n3wb_main.png");
}

void display_payload_active() {
    draw_image(tft, "/n3wb_main_evil.png");
}
