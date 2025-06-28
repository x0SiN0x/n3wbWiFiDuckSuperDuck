#include "payloads.hpp"
#include <FS.h>
#include <SD.h>
#include <LittleFS.h>
#include <vector>

fs::FS& getPayloadFS() {
    static bool sd_ok = SD.begin();
    return sd_ok ? (fs::FS&)SD : (fs::FS&)LittleFS;
}

std::vector<String> list_payloads() {
    std::vector<String> payloads;
    fs::FS &fs = getPayloadFS();
    File dir = fs.open("/payloads");

    if (!dir || !dir.isDirectory()) return payloads;

    File entry;
    while ((entry = dir.openNextFile())) {
        String name = entry.name();
        if (name.endsWith(".ds")) {
            payloads.push_back(name);
        }
        entry.close();
    }

    return payloads;
}

File open_payload(const String& name) {
    return getPayloadFS().open("/payloads/" + name, FILE_READ);
}
