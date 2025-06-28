
#include "api.hpp"
#include "api_log.hpp"
#include "api_live.hpp"
#include <Arduino.h>
#include <WebServer.h>

WebServer server(80);

void setupWebAPI() {
    Serial.println("[WebAPI] Registering routes");

    server.on("/status", HTTP_GET, []() {
        server.send(200, "application/json", R"({"status": "ok"})");
    });

    server.on("/payloads", HTTP_GET, []() {
        // In a real build this would list payloads from internal flash or SD
        server.send(200, "application/json", R"(["hello.txt","evil.txt"])");
    });

    server.on("/run", HTTP_POST, []() {
        String body = server.arg("plain");
        Serial.println("[WebAPI] Running payload:
" + body);
        // TODO: parse/execute payload here
        server.send(200, "application/json", R"({"status": "started"})");
    });

    server.begin();
    Serial.println("[WebAPI] Server started on port 80");
}
