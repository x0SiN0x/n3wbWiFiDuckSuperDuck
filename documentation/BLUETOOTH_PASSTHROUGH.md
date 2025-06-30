
# 🔌 Bluetooth Passthrough Feature – Technical Overview

The **Bluetooth Passthrough** feature allows the ESP32 device to act as a **bridge** between a Bluetooth HID device (e.g., keyboard, mouse) and a USB host (e.g., a PC). It captures HID input from a paired Bluetooth device and forwards the input as USB HID output to the connected computer.

Additionally, it supports **keylogging** of the captured input to internal SPIFFS or SD storage.

---

## 📐 Architecture

```
[ Bluetooth HID Peripheral ]
      ⬇ (BT HID Reports)
[  ESP32 – Central Mode  ]
      ⬇ (USB HID Reports)
[ Host Computer (USB) ]
```

---

## 🔧 How It Works

1. ESP32 acts as a **Bluetooth Central** and connects to a nearby HID device.
2. HID reports (key presses, mouse moves) are received via BT.
3. Reports are translated into **USB HID packets** and forwarded.
4. Input is optionally logged to a file in `/logs/bt_keys.log`.

---

## ⚙️ Feature Activation

### ✅ Compile-Time Requirements

In `platformio.ini`:

```ini
build_flags =
  -DHAS_BT
  -DHAS_USB
  -DHAS_HID
```

---

### ✅ Runtime Requirements

1. Enable the feature in NVS config:
   - `bt_enabled = true`
   - `bt_mode = "passthrough"`
   - `keylogger_enabled = true` (optional)
2. Set via WebUI Config tab or directly with `ConfigManager::get()` in code.

---

## 🐤 Duckyscript Integration

You can start passthrough mode from a script using:

```plaintext
ATTACKMODE BT_PASSTHROUGH
```

This configures the ESP32 to:
- Connect to paired BT devices
- Forward HID input to host
- Log data (if enabled)

---

## 🗂️ Key Logging

If `keylogger_enabled = true`, all keyboard events from the BT device are logged to:

```plaintext
/logs/bt_keys.log
```

Logged format (example):

```
[BT] KEY_PRESS: a
[BT] KEY_PRESS: Shift + R
[BT] MOUSE_MOVE: dx=3 dy=1
```

Works on both SPIFFS and SD depending on `msc_use_sd` flag.

---

## 🛠 Example: WebUI Config JSON

```json
{
  "bt_enabled": true,
  "bt_mode": "passthrough",
  "keylogger_enabled": true
}
```

---

## 🔐 Security Notes

- This feature is intended for **authorized diagnostic and input forwarding only**.
- Logs can expose sensitive input; disable `keylogger_enabled` for privacy-sensitive deployments.
- Ensure WebUI and filesystem access are protected in shared environments.

---

## 📘 Summary

Bluetooth Passthrough mode is ideal for:
- Capturing input from Bluetooth devices and replaying on USB
- Creating hybrid HID bridges for remote or stealth automation
- Auditing/recording input behavior in test scenarios

