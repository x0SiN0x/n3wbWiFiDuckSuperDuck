
#include <unity.h>
#include "config/config_manager.hpp"

void test_autorun_enabled_path() {
  ConfigManager::get().autorun_enabled = true;
  ConfigManager::get().autorun_payload_path = "/payloads/auto.ds";
  ConfigManager::save();
  ConfigManager::get().autorun_payload_path = "";
  ConfigManager::load();
  TEST_ASSERT_TRUE(ConfigManager::get().autorun_enabled);
  TEST_ASSERT_EQUAL_STRING("/payloads/auto.ds", ConfigManager::get().autorun_payload_path.c_str());
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_autorun_enabled_path);
  UNITY_END();
}

void loop() {}
