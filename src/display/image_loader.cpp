// Image loading: implements LOAD_PNG and LOAD_JPG
#include "LGFX_Config.hpp"
#include <FS.h>
#include <SD.h>

extern LGFX tft;

void draw_image(LGFX& tft, const char* path) {
    String file = String(path);
    fs::FS& fs = file.startsWith("/sd/") ? SD : SPIFFS;
    String shortPath = file.startsWith("/sd/") ? file.substring(3) : file;

    if (file.endsWith(".png")) {
        tft.drawPngFile(fs, shortPath);
    } else if (file.endsWith(".jpg") || file.endsWith(".jpeg")) {
        tft.drawJpgFile(fs, shortPath);
    }
}
