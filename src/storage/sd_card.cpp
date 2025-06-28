#include <SD_MMC.h>

bool sd_init() {
#if defined(USE_SD_MMC_INTERFACE)
    if (!SD_MMC.begin()) {
        Serial.println("SD_MMC mount failed.");
        return false;
    }
    Serial.println("SD_MMC mounted.");
#else
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD SPI mount failed.");
        return false;
    }
    Serial.println("SD SPI mounted.");
#endif
    return true;
}
