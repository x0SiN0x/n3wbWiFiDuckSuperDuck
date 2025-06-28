#include "../display/LGFX_Config.hpp"
#include "../images/n3wb_main_img.hpp"
#include "../images/n3wb_main_evil_img.hpp"

extern LGFX tft;

void draw_builtin_image(bool evil = false) {
  if (evil) {
    tft.pushImage(0, 0, 160, 80, n3wb_main_evil_img);
  } else {
    tft.pushImage(0, 0, 160, 80, n3wb_main_img);
  }
}
