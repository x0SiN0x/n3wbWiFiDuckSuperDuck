// Handles .ds payload file discovery and loading
#include "payloads.hpp"
#include <FS.h>
#include <SD.h>
#include <vector>

std::vector<String> list_payloads() {
    std::vector<String> payloads;
    File dir = SD.open("/payloads");

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
    String path = "/payloads/" + name;
    return SD.open(path, FILE_READ);
}
