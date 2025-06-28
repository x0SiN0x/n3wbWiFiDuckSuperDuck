#include "webui_api_backend.hpp"

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"


// Simulated system values (replace with real metrics)
int getCPULoad() { return 15; }
int getFreeRAM() { return 3400; }
String getDiskUsage() { return "1.2MB / 4MB"; }
bool isPayloadActive() { return false; }

void setupWebAPI() {
  // Serve /api/status
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request){
    DynamicJsonDocument doc(256);
    doc["cpu"] = getCPULoad();
    doc["ram"] = getFreeRAM();
    doc["disk"] = getDiskUsage();
    doc["active"] = isPayloadActive();
    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
  });

  // Serve /api/payloads
  server.on("/api/payloads", HTTP_GET, [](AsyncWebServerRequest *request){
    DynamicJsonDocument doc(1024);
    JsonArray arr = doc.to<JsonArray>();
    File root = SPIFFS.open("/payloads");
    if (!root || !root.isDirectory()) {
      request->send(500, "application/json", "[]");
      return;
    }
    File file = root.openNextFile();
    while (file) {
      arr.add(String(file.name()).substring(10)); // Strip /payloads/
      file = root.openNextFile();
    }
    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
  });

  // Serve /api/payloads/<name>
  server.on(R"(^/api/payloads/([\w\d_-]+\.txt)$)", HTTP_GET, [](AsyncWebServerRequest *request){
    String name = request->pathArg(0);
    String path = "/payloads/" + name;
    if (!SPIFFS.exists(path)) {
      request->send(404, "text/plain", "Not Found");
      return;
    }
    File f = SPIFFS.open(path, FILE_READ);
    String content = f.readString();
    f.close();
    request->send(200, "text/plain", content);
  });

  // POST /api/hid/keyboard
  server.on("/api/hid/keyboard", HTTP_POST, [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
      StaticJsonDocument<128> doc;
      DeserializationError err = deserializeJson(doc, data);
      if (!err && doc.containsKey("key")) {
        String key = doc["key"].as<String>();
        // TODO: call sendKey(key); implement real HID logic
        Serial.printf("[HID] Key: %s\n", key.c_str());
      }
      request->send(200);
    }
  );

  // POST /api/hid/mouse
  server.on("/api/hid/mouse", HTTP_POST, [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
      StaticJsonDocument<128> doc;
      DeserializationError err = deserializeJson(doc, data);
      if (!err && doc.containsKey("action")) {
        String action = doc["action"].as<String>();
        // TODO: call moveMouse(action); implement real mouse logic
        Serial.printf("[HID] Mouse: %s\n", action.c_str());
      }
      request->send(200);
    }
  );

  // POST /api/config
  server.on("/api/config", HTTP_POST, [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
      StaticJsonDocument<512> doc;
      DeserializationError err = deserializeJson(doc, data);
      if (err) {
        request->send(400, "text/plain", "Invalid JSON");
        return;
      }
      // Save settings to NVS or global vars (e.g., doc["key-delay"])
      Serial.println("[CONFIG] Received settings:");
      serializeJsonPretty(doc, Serial);
      request->send(200, "text/plain", "OK");
    }
  );
}
