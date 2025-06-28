#include <FS.h>
#include <LittleFS.h>
#include <SD.h>
#include "LGFX_Config.hpp"
#include "image_loader.hpp"

extern LGFX tft;

void draw_image(LGFX& tft, const char* path) {
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS mount failed");
        return;
    }

    String file = String(path);
    fs::FS &fs = file.startsWith("/sd/") ? (fs::FS &)SD : (fs::FS &)LittleFS;
    String shortPath = file.startsWith("/sd/") ? file.substring(3) : file;

    if (file.endsWith(".png")) {
        tft.drawPngFile(fs, shortPath.c_str());
    } else if (file.endsWith(".jpg") || file.endsWith(".jpeg")) {
        tft.drawJpgFile(fs, shortPath.c_str());
    }
}
