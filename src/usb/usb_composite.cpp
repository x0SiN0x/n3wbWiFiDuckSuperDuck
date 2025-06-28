#include "usb_composite.hpp"
#include "tusb.h"
#include "../storage/msc.hpp"

void usb_init_composite(bool enable_hid, bool enable_storage) {
    tusb_init();

    if (enable_hid) {
        // tud_hid_set_report_cb(hid_report_callback); // define callback later if needed
    }

    if (enable_storage) {
        storage_mount_msc_luns();
    }
}
