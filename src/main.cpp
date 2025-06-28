#include <Arduino.h>
#include <WiFi.h>
#include "webui/web_server.hpp"
#include "display/LGFX_Config.hpp"
#include "display/image_loader.hpp"
#include "webui/api_log.hpp"

LGFX tft;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("[BOOT] Setup() started");
  logln("[BOOT] Setup() started");

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  draw_image(tft, "/n3wb_main.png");
  logln("[DISPLAY] TFT initialized and splash loaded");

  WiFi.softAP("n3wbDuck", "newbpass");
  Serial.println("[WIFI] Access Point started: n3wbDuck");
  logln("[WIFI] Access Point started");

  start_web_server();
  logln("[WEB] Web server started");
}

void loop() {
  delay(100);
}
