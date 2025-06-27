#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "api.hpp"

AsyncWebServer server(80);

void start_web_server() {
  WiFi.softAP("n3wbDuck", "newbpass");
  Serial.println("WiFi AP started: n3wbDuck");

  init_api_routes(server); // Register /status, /payloads, etc.

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
