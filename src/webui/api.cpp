#include <ESPAsyncWebServer.h>
#include "api.hpp"
#include "../storage/payloads.hpp"

extern bool isPayloadRunning;
extern String getKeyboardLayout();

String getMetricsJson() {
  return String("{") +
         "\"cpu\": 18, \"ram\": 72, \"layout\": \"" + getKeyboardLayout() +
         "\", \"running\": " + (isPayloadRunning ? "true" : "false") + " }";
}

void init_api_routes(AsyncWebServer &server) {
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", getMetricsJson());
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", "{ \"layout\": \"US\", \"default_delay\": 5 }");
  });

  server.on("/config", HTTP_POST, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", "{ \"saved\": true }");
  });
}
