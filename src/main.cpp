#include <Arduino.h>
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "duckyscript/DuckyInterpreter.h"

DuckyInterpreter ducky;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Try SD
  bool sdFound = false;
  if (SD.begin()) {
    Serial.println("[MAIN] SD card initialized.");
    File f = SD.open("/inject.txt");
    if (f) {
      String script;
      while (f.available()) script += (char)f.read();
      f.close();
      ducky.setAttackMode(true, true);
      ducky.loadScript(script);
      ducky.run();
      sdFound = true;
    }
  }

  // Try internal (SPIFFS, etc.) if SD fails
  if (!sdFound) {
    Serial.println("[MAIN] Looking for internal inject.txt");
    File f = SPIFFS.open("/inject.txt");
    if (f) {
      String script;
      while (f.available()) script += (char)f.read();
      f.close();
      ducky.setAttackMode(true, false);
      ducky.loadScript(script);
      ducky.run();
    } else {
      Serial.println("[MAIN] No inject.txt found.");
    }
  }
}

void loop() {
  delay(100);
}