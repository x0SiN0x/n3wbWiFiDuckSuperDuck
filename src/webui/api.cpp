#include <ESPAsyncWebServer.h>
#include "api.hpp"
#include "../storage/payloads.hpp"

extern bool isPayloadRunning;
extern String getKeyboardLayout();

// Placeholder system metrics
String getMetricsJson() {
  return "{ "cpu": 18, "ram": 72, "layout": "" + getKeyboardLayout() + "", "running": " + (isPayloadRunning ? "true" : "false") + " }";
}

void init_api_routes(AsyncWebServer &server) {
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", getMetricsJson());
  });

  server.on("/payloads", HTTP_GET, [](AsyncWebServerRequest *req) {
    std::vector<String> list = list_payloads();
    String json = "[";
    for (size_t i = 0; i < list.size(); ++i) {
      json += """ + list[i] + """;
      if (i != list.size() - 1) json += ",";
    }
    json += "]";
    req->send(200, "application/json", json);
  });

  server.on("/payload/load", HTTP_GET, [](AsyncWebServerRequest *req) {
    if (!req->hasParam("name")) return req->send(400);
    String name = req->getParam("name")->value();
    File f = open_payload(name);
    if (!f) return req->send(404);
    String content = f.readString();
    f.close();
    req->send(200, "text/plain", content);
  });

  server.on("/payload/save", HTTP_POST, [](AsyncWebServerRequest *req) {
    if (!req->hasParam("name")) return req->send(400);
    String name = req->getParam("name")->value();
    req->send(200, "text/plain", "OK"); // Stub — add real saving
  });

  server.on("/payload/run", HTTP_POST, [](AsyncWebServerRequest *req) {
    if (!req->hasParam("name")) return req->send(400);
    String name = req->getParam("name")->value();
    // runScript(open_payload(name));
    req->send(200, "text/plain", "Running " + name);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", "{ "layout": "US", "default_delay": 5 }");
  });

  server.on("/config", HTTP_POST, [](AsyncWebServerRequest *req) {
    req->send(200, "application/json", "{ "saved": true }");
  });
}
