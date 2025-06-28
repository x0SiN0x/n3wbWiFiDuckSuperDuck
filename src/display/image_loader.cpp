#include <FS.h>
#include <SPIFFS.h>
#include <SD.h>
#include "LGFX_Config.hpp"
#include "image_loader.hpp"

extern LGFX tft;

void draw_image(LGFX& tft, const char* path) {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS mount failed");
        return;
    }

    String file = String(path);
    fs::FS& fs = file.startsWith("/sd/") ? SD : SPIFFS;
    String shortPath = file.startsWith("/sd/") ? file.substring(3) : file;

    if (file.endsWith(".png")) {
        tft.drawPngFile(shortPath.c_str());
    } else if (file.endsWith(".jpg") || file.endsWith(".jpeg")) {
        tft.drawJpgFile(shortPath.c_str());
    }
}
