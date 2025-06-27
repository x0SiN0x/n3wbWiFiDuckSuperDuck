// Composite USB descriptor and class registration
#include "usb_descriptors.h"
#include "tusb.h"
#include "usb_composite.hpp"

void usb_init_composite(bool enable_hid, bool enable_storage) {
    tusb_init();

    if (enable_hid) {
        // HID driver (keyboard/mouse/media)
        tud_hid_set_report_cb(hid_report_callback);
    }

    if (enable_storage) {
        // MSC driver initialized via msc.cpp
        storage_mount_msc_luns();
    }
}
