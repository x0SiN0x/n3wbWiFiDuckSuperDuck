#pragma once
#include <Arduino.h>
#include <FS.h>
#include <vector>

std::vector<String> list_payloads();
File open_payload(const String& name);
