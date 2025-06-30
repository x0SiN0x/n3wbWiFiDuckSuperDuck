
#include <unity.h>
#include "config/config_manager.hpp"

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

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_config_load_defaults);
  RUN_TEST(test_config_save_reload);
  UNITY_END();
}

void loop() {}
