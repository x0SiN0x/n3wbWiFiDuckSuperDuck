// File: include/config/config_manager.hpp
#pragma once
#include <string>
#include <Preferences.h>

struct Config {
  bool usb_enabled;
  bool hid_enabled;
  bool msc_enabled;
  bool use_sd;
  std::string layout;
  int default_delay;
  int key_press_delay;
  bool bt_enabled;
  std::string bt_mode;
  bool keylogger_enabled;
  bool tft_enabled;
  int tft_brightness;
  bool autorun_enabled;
  std::string autorun_payload_path;
};

class ConfigManager {
public:
  static inline Config& get() {
    return config();
  }
  static inline void load() {
    Preferences prefs;
    prefs.begin("config", true);
    cfg().layout = prefs.getString("layout", "us").c_str();
    cfg().default_delay = prefs.getInt("default_delay", 50);
    cfg().key_press_delay = prefs.getInt("key_press_delay", 5);
    cfg().bt_mode = prefs.getString("bt_mode", "passthrough").c_str();
    cfg().bt_enabled = prefs.getBool("bt_enabled", true);
    cfg().hid_enabled = prefs.getBool("hid_enabled", true);
    cfg().msc_enabled = prefs.getBool("msc_enabled", true);
    cfg().use_sd = prefs.getBool("use_sd", false);
    cfg().tft_enabled = prefs.getBool("tft_enabled", true);
    cfg().tft_brightness = prefs.getInt("tft_brightness", 255);
    cfg().keylogger_enabled = prefs.getBool("keylogger_enabled", false);
    cfg().autorun_enabled = prefs.getBool("autorun_enabled", false);
    cfg().autorun_payload_path = prefs.getString("autorun_path", "/payloads/auto.ds").c_str();
    prefs.end();
  }
  static inline void save() {
    Preferences prefs;
    prefs.begin("config", false);
    prefs.putString("layout", cfg().layout.c_str());
    prefs.putInt("default_delay", cfg().default_delay);
    prefs.putInt("key_press_delay", cfg().key_press_delay);
    prefs.putString("bt_mode", cfg().bt_mode.c_str());
    prefs.putBool("bt_enabled", cfg().bt_enabled);
    prefs.putBool("hid_enabled", cfg().hid_enabled);
    prefs.putBool("msc_enabled", cfg().msc_enabled);
    prefs.putBool("use_sd", cfg().use_sd);
    prefs.putBool("tft_enabled", cfg().tft_enabled);
    prefs.putInt("tft_brightness", cfg().tft_brightness);
    prefs.putBool("keylogger_enabled", cfg().keylogger_enabled);
    prefs.putBool("autorun_enabled", cfg().autorun_enabled);
    prefs.putString("autorun_path", cfg().autorun_payload_path.c_str());
    prefs.end();
  }

private:
  static inline Config &cfg() { static Config inst; return inst; }
  static inline Config &config() { return cfg(); }
};