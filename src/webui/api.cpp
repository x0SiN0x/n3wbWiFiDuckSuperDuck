#include <ESPAsyncWebServer.h>
#include "api.hpp"
#include "../storage/payloads.hpp"
#include "../duckyscript/layout_manager.hpp"

extern bool isPayloadRunning;
extern LayoutManager layout_manager;

String getMetricsJson() {
  return String("{") +
         "\"cpu\": 18, \"ram\": 72, \"layout\": \"" + layout_manager.getCurrentLayout() +
         "\", \"running\": " + (isPayloadRunning ? "true" : "false") + " }";
}

void init_api_routes(AsyncWebServer &server) {
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", getMetricsJson());
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", "{ \"layout\": \"" + layout_manager.getCurrentLayout() + "\" }");
  });

  server.on("/config", HTTP_POST, [](AsyncWebServerRequest *req) {}, NULL,
    [](AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t, size_t) {
      String json = String((char*)data);
      int start = json.indexOf(":") + 2;
      int end = json.lastIndexOf("\"");
      String layout = json.substring(start, end);
      layout_manager.setLayout(layout);
      req->send(200, "application/json", "{ \"saved\": true }");
    }
  );
}
