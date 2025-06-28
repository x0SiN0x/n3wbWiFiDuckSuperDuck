#pragma once
#include <ESPAsyncWebServer.h>

void init_log_route(AsyncWebServer& server);
void logToBuffer(const char* msg);
