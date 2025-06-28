#pragma once
#include <ESPAsyncWebServer.h>

void init_log_route(AsyncWebServer& server);
void logToBuffer(const char* msg);
void log(const String& msg);
void logln(const String& msg);
