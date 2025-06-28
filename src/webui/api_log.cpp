#include "api_log.hpp"

#define LOG_BUFFER_SIZE 4096
char logBuffer[LOG_BUFFER_SIZE];
size_t logPos = 0;

void logToBuffer(const char* msg) {
  size_t len = strlen(msg);
  for (size_t i = 0; i < len; ++i) {
    logBuffer[(logPos++) % LOG_BUFFER_SIZE] = msg[i];
  }
}

String getLogBuffer() {
  String result;
  for (size_t i = 0; i < LOG_BUFFER_SIZE; ++i) {
    char c = logBuffer[(logPos + i) % LOG_BUFFER_SIZE];
    result += c;
  }
  return result;
}

void init_log_route(AsyncWebServer& server) {
  server.on("/log", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(200, "text/plain", getLogBuffer());
  });
}

void logln(const String& msg) {
  Serial.println(msg);
  logToBuffer((msg + "\n").c_str());
}

void log(const String& msg) {
  Serial.print(msg);
  logToBuffer(msg.c_str());
}
