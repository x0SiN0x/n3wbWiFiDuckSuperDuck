
#include <Arduino.h>
#include "duckyscript/parser.hpp"
#include "duckyscript/runner.hpp"

void test_duckyscript_parser(const std::string& script) {
    DuckyParser parser;
    auto result = parser.parse(script);
    if (!result.success) {
        Serial.println("Test failed: " + result.error);
    } else {
        Serial.println("Test passed.");
    }
}

void setup() {
    Serial.begin(115200);
    test_duckyscript_parser("DEFAULT_DELAY 100\nSTRING Hello World\nENTER");
    test_duckyscript_parser("KEY_PRESS_DELAY 50\nSTRING Test123\nENTER");
    test_duckyscript_parser("LOAD_PNG splash.png\nSTRING Welcome!");
    test_duckyscript_parser("IF TRUE\nSTRING Condition Met\nENDIF");
}

void loop() {}
