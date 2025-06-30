// File: include/config/config_manager.hpp
#pragma once
#include <string>

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
  static void load();
  static void save();
  static Config& get();
};