#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "api.hpp"
#include "api_live.hpp"

AsyncWebServer server(80);

void start_web_server() {
  if (!SPIFFS.begin(true)) {
    Serial.println("[SPIFFS] Mount failed");
    return;
  } else {
    Serial.println("[SPIFFS] Mounted");
  }


  init_api_routes(server);
  init_live_routes(server);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/pages/main.html", "text/html");
  });

  server.on("/config.html", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/pages/config.html", "text/html");
  });

  server.on("/about.html", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/pages/about.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("main.html");

  server.begin();
}
