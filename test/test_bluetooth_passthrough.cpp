
#include <unity.h>
#include "config/config_manager.hpp"

void test_bt_passthrough_enable() {
  ConfigManager::get().bt_enabled = true;
  ConfigManager::get().bt_mode = "passthrough";
  ConfigManager::save();
  ConfigManager::load();
  TEST_ASSERT_TRUE(ConfigManager::get().bt_enabled);
  TEST_ASSERT_EQUAL_STRING("passthrough", ConfigManager::get().bt_mode.c_str());
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_bt_passthrough_enable);
  UNITY_END();
}

void loop() {}
