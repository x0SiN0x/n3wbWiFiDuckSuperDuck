#include <Arduino.h>

void storage_mount_msc_luns() {
#ifdef HAS_SD
    Serial.println("MSC: SD available for second LUN");
#endif
}
