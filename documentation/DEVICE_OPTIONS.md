
# 📦 DEVICE_OPTIONS.md

This document describes all feature flags and configuration settings available in the n3wbWiFiDuckSuperDuck firmware. These control what features are compiled into the firmware and how they behave at runtime.

---

## ⚙️ PlatformIO Build Flags

These are defined in your `platformio.ini` file:

```ini
build_flags =
  -DHAS_USB
  -DHAS_MSC
  -DHAS_HID
  -DHAS_SD
  -DHAS_TFT
  -DHAS_BT
```

---

### 🔌 `HAS_USB`
- **Enables**: USB composite stack (HID, MSC)
- **Used in**: `usb_config.cpp`, `usb_composite.cpp`, `main.cpp`
- **NVS key**: `usb_enabled`
- **Required for**: `ATTACKMODE HID`, `ATTACKMODE STORAGE`

---

### 💾 `HAS_MSC`
- **Enables**: USB Mass Storage support
- **Depends on**: `HAS_USB`
- **Used in**: `msc.cpp`, `usb_composite.cpp`
- **NVS keys**:
  - `msc_enabled`
  - `msc_use_sd`
- **Runtime**: Mounts SD or SPIFFS as USB drive

---

### 🎹 `HAS_HID`
- **Enables**: USB HID (keyboard, mouse, media)
- **Used in**: `usb_hid_keyboard.cpp`, `usb_hid_mouse.cpp`
- **NVS keys**:
  - `hid_enabled`
  - `layout`
  - `default_delay`, `key_press_delay`

---

### 💽 `HAS_SD`
- **Enables**: SD card support
- **Used in**: `sd_card.cpp`, `file_executor.cpp`
- **NVS key**: `use_sd_storage`
- **Runtime**: Used for file I/O, RUNFILE, MSC backend

---

### 🖼 `HAS_TFT`
- **Enables**: TFT display support
- **Used in**: `display.cpp`, `image_loader.cpp`
- **NVS keys**:
  - `tft_enabled`
  - `tft_brightness`
- **Duckyscript**: Supports `LOAD_PNG`, `TFT_TEXT`, etc.

---

### 📶 `HAS_BT`
- **Enables**: Bluetooth HID, passthrough, keylogging
- **Used in**: `bt_hid.cpp`, `bt_passthrough.cpp`
- **NVS keys**:
  - `bt_enabled`
  - `bt_mode`: `scripted` or `passthrough`
  - `keylogger_enabled`
- **Duckyscript**: `ATTACKMODE BT_HID`, `ATTACKMODE BT_PASSTHROUGH`

---

## 🧠 NVS Config Keys

| Key                   | Type     | Used For                         |
|------------------------|----------|----------------------------------|
| `usb_enabled`         | `bool`   | Enable/disable USB               |
| `hid_enabled`         | `bool`   | Enable HID output                |
| `msc_enabled`         | `bool`   | Enable mass storage              |
| `msc_use_sd`          | `bool`   | Use SD (true) or SPIFFS (false)  |
| `layout`              | `string` | Keyboard layout (us, fr, etc.)   |
| `default_delay`       | `int`    | Delay between lines in ms        |
| `key_press_delay`     | `int`    | Delay between key presses in ms  |
| `bt_enabled`          | `bool`   | Enable Bluetooth stack           |
| `bt_mode`             | `string` | `scripted` or `passthrough`      |
| `keylogger_enabled`   | `bool`   | Log BT input to file             |
| `autorun_payload`     | `string` | Path to script to run on boot    |
| `tft_enabled`         | `bool`   | Enable TFT                       |
| `tft_brightness`      | `int`    | Brightness level (0–255)         |

---

## 🧩 Runtime Integration Example

```cpp
#ifdef HAS_USB
  initUSB(); // uses NVS to decide HID, MSC modes
#endif

#ifdef HAS_TFT
  if (config.tft_enabled) {
    tft.begin();
    tft.setBrightness(config.tft_brightness);
  }
#endif

#ifdef HAS_BT
  if (config.bt_enabled) {
    if (config.bt_mode == "passthrough")
      startBluetoothPassthrough();
    else
      startBluetoothScripted();
  }
#endif
```

This approach ensures minimal firmware size per target while maximizing runtime flexibility.
