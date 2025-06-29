#include <LittleFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "api.hpp"
#include "api_live.hpp"
#include "webui_api_backend.hpp"

void startWebServer() {
  if (!LittleFS.begin(true)) {
    Serial.println("[LittleFS] Mount failed");
    return;
  } else {
    Serial.println("[LittleFS] Mounted");
  }


  setupWebAPI();
  init_live_routes(server);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(LittleFS, "/pages/main.html", "text/html");
  });

  server.on("/config.html", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(LittleFS, "/pages/config.html", "text/html");
  });

  server.on("/about.html", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(LittleFS, "/pages/about.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/").setDefaultFile("main.html");

  server.begin();
}
