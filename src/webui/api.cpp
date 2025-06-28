
#include "api.hpp"
#include "api_log.hpp"
#include "api_live.hpp"
#include "webui_api_backend.hpp"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void setupWebAPI() {
    Serial.println("[WebAPI] Registering routes");

    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *req) {
        req->send(200, "application/json", R"({"status": "ok"})");
    });

    server.on("/payloads", HTTP_GET, [](AsyncWebServerRequest *req) {
        // In a real build this would list payloads from internal flash or SD
        req->send(200, "application/json", R"(["hello.txt","evil.txt"])");
    });

    server.on("/run", HTTP_POST, [](AsyncWebServerRequest *req) {
        String body = req->arg("plain");
        Serial.println("[WebAPI] Running payload: " + body);
        // TODO: parse/execute payload here
        req->send(200, "application/json", R"({"status": "started"})");
    });

    // server.begin(); // started elsewhere
}
