// File: src/main.cpp
#include <Arduino.h>

#ifdef HAS_TFT
#include "display/display.hpp"
#include "display/LGFX_Config.hpp"
#endif

#ifdef HAS_USB
#include "usb/usb_config.hpp"
#endif

#ifdef HAS_SD
#include "storage/sd_card.hpp"
#endif

#ifdef HAS_BT
#include "bt/bt_passthrough.hpp"
#endif

#include "config/config_manager.hpp"
#include "web/web_server.hpp"
#include "duckyscript/duckyscript_engine.hpp"

extern LGFX tft;

void setup() {
  Serial.begin(115200);

#ifdef HAS_TFT
  if (ConfigManager::get().tft_enabled) {
    tft.begin();
    tft.setBrightness(ConfigManager::get().tft_brightness);
    showIdleScreen();
  }
#endif

#ifdef HAS_USB
  initUSB(); // checks NVS config for HID + MSC
#endif

  initStorage();  // SPIFFS or SD

#ifdef HAS_BT
  if (ConfigManager::get().bt_enabled) {
    if (ConfigManager::get().bt_mode == "passthrough") {
      startBluetoothPassthrough();
    } else {
      startBluetoothHID();
    }
  }
#endif

  ConfigManager::load(); // load NVS
  startWebServer(); // WebUI
  duckyscript::init();  // Runtime environment

  if (ConfigManager::get().autorun_enabled) {
    duckyscript::runFile(ConfigManager::get().autorun_payload_path.c_str());
  }
}

void loop() {
  handleWebRequests();  // optional async loop
}