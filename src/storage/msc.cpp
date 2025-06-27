// MSC dual LUN configuration
#include "msc.hpp"

void storage_mount_msc_luns() {
    // Mount internal flash (LUN 0)
    // Mount SD card if HAS_SD (LUN 1)
#ifdef HAS_SD
    // Future: LUN1 init logic here (TinyUSB)
    Serial.println("MSC: SD available for second LUN");
#endif
}
