#include <Arduino.h>
#include <unity.h>
#include "config/config_manager.hpp"
#include "duckyscript/parser.hpp"

void test_autorun_enabled_path() {
  ConfigManager::get().autorun_enabled = true;
  ConfigManager::get().autorun_payload_path = "/payloads/auto.ds";
  ConfigManager::save();
  ConfigManager::get().autorun_payload_path = "";
  ConfigManager::load();
  TEST_ASSERT_TRUE(ConfigManager::get().autorun_enabled);
  TEST_ASSERT_EQUAL_STRING("/payloads/auto.ds", ConfigManager::get().autorun_payload_path.c_str());
}

void test_bt_passthrough_enable() {
  ConfigManager::get().bt_enabled = true;
  ConfigManager::get().bt_mode = "passthrough";
  ConfigManager::save();
  ConfigManager::load();
  TEST_ASSERT_TRUE(ConfigManager::get().bt_enabled);
  TEST_ASSERT_EQUAL_STRING("passthrough", ConfigManager::get().bt_mode.c_str());
}

void test_config_load_defaults() {
  ConfigManager::load();
  TEST_ASSERT_EQUAL_STRING("us", ConfigManager::get().layout.c_str());
}

void test_config_save_reload() {
  ConfigManager::get().layout = "de";
  ConfigManager::save();
  ConfigManager::get().layout = "";
  ConfigManager::load();
  TEST_ASSERT_EQUAL_STRING("de", ConfigManager::get().layout.c_str());
}

void test_duckyscript_parser_basic() {
  DuckyParser parser;
  ParseResult res1 = parser.parse(String("DEFAULT_DELAY 100\nSTRING Hello World\nENTER"));
  TEST_ASSERT_TRUE(res1.success);
  ParseResult res2 = parser.parse(String("KEY_PRESS_DELAY 50\nSTRING Test123\nENTER"));
  TEST_ASSERT_TRUE(res2.success);
  ParseResult res3 = parser.parse(String("LOAD_PNG splash.png\nSTRING Welcome!"));
  TEST_ASSERT_TRUE(res3.success);
  ParseResult res4 = parser.parse(String("IF TRUE\nSTRING Condition Met\nENDIF"));
  TEST_ASSERT_TRUE(res4.success);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_autorun_enabled_path);
  RUN_TEST(test_bt_passthrough_enable);
  RUN_TEST(test_config_load_defaults);
  RUN_TEST(test_config_save_reload);
  RUN_TEST(test_duckyscript_parser_basic);
  UNITY_END();
}

void loop() {}
