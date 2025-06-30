// File: src/config/config_manager.cpp
#include "config/config_manager.hpp"
#include <Preferences.h>

static Config config;

void ConfigManager::load() {
  Preferences prefs;
  prefs.begin("config", true);
  config.layout = prefs.getString("layout", "us").c_str();
  config.default_delay = prefs.getInt("default_delay", 50);
  config.key_press_delay = prefs.getInt("key_press_delay", 5);
  config.bt_mode = prefs.getString("bt_mode", "passthrough").c_str();
  config.bt_enabled = prefs.getBool("bt_enabled", true);
  config.hid_enabled = prefs.getBool("hid_enabled", true);
  config.msc_enabled = prefs.getBool("msc_enabled", true);
  config.use_sd = prefs.getBool("use_sd", false);
  config.tft_enabled = prefs.getBool("tft_enabled", true);
  config.tft_brightness = prefs.getInt("tft_brightness", 255);
  config.keylogger_enabled = prefs.getBool("keylogger_enabled", false);
  config.autorun_enabled = prefs.getBool("autorun_enabled", false);
  config.autorun_payload_path = prefs.getString("autorun_path", "/payloads/auto.ds").c_str();
  prefs.end();
}

void ConfigManager::save() {
  Preferences prefs;
  prefs.begin("config", false);
  prefs.putString("layout", config.layout.c_str());
  prefs.putInt("default_delay", config.default_delay);
  prefs.putInt("key_press_delay", config.key_press_delay);
  prefs.putString("bt_mode", config.bt_mode.c_str());
  prefs.putBool("bt_enabled", config.bt_enabled);
  prefs.putBool("hid_enabled", config.hid_enabled);
  prefs.putBool("msc_enabled", config.msc_enabled);
  prefs.putBool("use_sd", config.use_sd);
  prefs.putBool("tft_enabled", config.tft_enabled);
  prefs.putInt("tft_brightness", config.tft_brightness);
  prefs.putBool("keylogger_enabled", config.keylogger_enabled);
  prefs.putBool("autorun_enabled", config.autorun_enabled);
  prefs.putString("autorun_path", config.autorun_payload_path.c_str());
  prefs.end();
}

Config& ConfigManager::get() {
  return config;
}