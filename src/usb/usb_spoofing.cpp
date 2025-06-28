#include <Arduino.h>
#include "usb_descriptors.h"

uint16_t get_usb_vid() {
#ifdef OPT_USB_VID
    return OPT_USB_VID;
#else
    return 0x1337;
#endif
}

uint16_t get_usb_pid() {
#ifdef OPT_USB_PID
    return OPT_USB_PID;
#else
    return 0x0001;
#endif
}
