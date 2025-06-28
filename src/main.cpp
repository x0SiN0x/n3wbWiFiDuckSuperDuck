#include <Arduino.h>
#include <WiFi.h>
#include "webui/web_server.hpp"
#include "display/LGFX_Config.hpp"
#include "display/image_builtin.hpp"
#include "webui/api_log.hpp"
#include "esp_task_wdt.h"

extern LGFX tft;

void setup() {
  // Correct WDT config for ESP-IDF 5+
  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = 10000,  // 10 seconds
    .idle_core_mask = (1 << portNUM_PROCESSORS) - 1,
    .trigger_panic = false
  };
  if (esp_task_wdt_status(NULL) == ESP_ERR_NOT_FOUND) {
    esp_task_wdt_init(&wdt_config);
  }
  esp_task_wdt_add(NULL);  // register current task

  Serial.begin(115200);
  delay(1000);
  Serial.println("[BOOT] Setup() started");
  logln("[BOOT] Setup() started");

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  draw_builtin_image(false);  // show embedded splash
  logln("[DISPLAY] Built-in splash loaded");

  WiFi.softAP(OPT_WIFI_SSID, OPT_WIFI_PASS);
  Serial.printf("[WIFI] Access Point started: %s / %s\n", OPT_WIFI_SSID, OPT_WIFI_PASS);
  logln(String("[WIFI] Access Point started: ") + OPT_WIFI_SSID);

  start_web_server();
  logln("[WEB] Web server started");

  tft.setTextSize(2);
  tft.setTextColor(TFT_RED);
  tft.drawString("TEST SCREEN", 10, 30);
}

void loop() {
  esp_task_wdt_reset();
  delay(100);
}
