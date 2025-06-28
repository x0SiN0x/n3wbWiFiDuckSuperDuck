#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include "webui/webui_api_backend.hpp"

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(500);

  // Init LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("❌ Failed to mount LittleFS");
    return;
  }
  Serial.println("✅ LittleFS mounted");

  // Connect to WiFi AP mode
  WiFi.softAP(OPT_WIFI_SSID, OPT_WIFI_PASS);
  Serial.println("📡 Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Mount static files (HTML, JS, CSS)
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  // Setup JSON API endpoints
  setupWebAPI();

  // Start server
  server.begin();
  Serial.println("🌐 Web server started");
}

void loop() {
  // No loop logic for now
}
