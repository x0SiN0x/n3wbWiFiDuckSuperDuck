// File: src/bt/bt_passthrough.cpp
#include "bt_passthrough.hpp"
#include "usb/usb_hid_keyboard.hpp"
#include "usb/usb_hid_mouse.hpp"
#include "storage/payloads.hpp"
#include <esp_log.h>

static const char* TAG = "BTPassthrough";

void startBluetoothPassthrough() {
  ESP_LOGI(TAG, "Starting Bluetooth Passthrough Mode");
}

void startBluetoothHID() {
  ESP_LOGI(TAG, "Starting Bluetooth HID Scripted Mode");
}