
#include <Arduino.h>

#ifdef HAS_TFT
#include "display/display.hpp"
#include "display/LGFX_Config.hpp"
#endif

#include "webui/web_server.hpp"
#include "duckyscript/duckyscript_engine.hpp"
#include "hid/hid_executor.hpp"
#include "usb/usb_config.hpp"
#include "storage/storage_manager.hpp"

extern LGFX tft;

void setup() {
  Serial.begin(115200);

#ifdef HAS_TFT
  tft.begin();
  tft.setBrightness(255);
  showIdleScreen();  // shows n3wb_main.png
#endif

  // Initialize USB stack (HID, Storage, etc.)
  initUSB();

  // Mount internal storage (SPIFFS) or SD card if present
  initStorage();

  // Start the WebUI server
  startWebServer();

  // Initialize Duckyscript system runtime context
  duckyscript::init();

  // Optionally: load saved config or script defaults from NVS (not yet implemented)
}

void loop() {
  // Background handling if needed
  handleWebRequests();  // typically runs in async loop
}
