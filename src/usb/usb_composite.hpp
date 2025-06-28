#pragma once
#include <Arduino.h>

void usb_init_composite(bool enable_hid, bool enable_storage);
void send_hid_key(uint8_t keycode);
void send_hid_combo(uint8_t *modifiers, uint8_t *keys, size_t len);
void send_media_key(uint8_t usage);
