# n3wb WiFiDuckSuperDuck

A fully modular, open-source USB HID injection platform built for ESP32-S3/S2 microcontrollers. Supports DuckyScript v1, v2, v3, and custom v3+ extensions. Comes with a fully integrated WebUI, live payload injection, TFT display support, SD storage, MSC dual-LUN mounting, and real-time device configuration.

> **Boards Supported**
>
> - LILYGO-T-Dongle-S3 (Primary test unit)
> - ESP32-S3-DevKitC-1 (16MB variant)
> - Waveshare ESP32-S3-GEEK
> - ESP32-S2-Kaluga-1 (4MB)

---

## ✨ Highlights

- ✈ **HID Combo Engine**: Keyboard, Mouse, and Media keys simultaneously
- 🖼 **TFT Status Display**: Real-time duck image switches based on activity
- 📂 **MSC Storage**: Internal flash + optional SD as USB drives (dual LUN)
- 📡 **Live WebUI**: Monaco-style payload editor, configuration manager
- 🔄 **Live Mode**: Real-time key/mouse/media injection from browser
- ⚡ **DuckyScript v1–v3+ Support**: Includes conditional logic, variables, functions, layout switching, PNG/JPG display
- 📷 **Self-hosted WebUI**: Fully embedded; no CDN required
- 🌍 **Captive Portal**: Instant connection from any mobile/desktop device

---

## 🌐 Web Interface

Access the WebUI by connecting to the device's AP (default SSID: `n3wbDuck`, password: `newbpass`):

- `/` — Main Page: duck status, metrics, payload editor
- `/config.html` — Configure USB spoofing, delays, layout
- `/about.html` — Project overview & Hak5 docs
- `/live.html` — Real-time injection tools

---

## 🏋 System Architecture

- `src/duckyscript/` — Full parser, VM, and instruction set
- `src/usb/` — TinyUSB stack (keyboard, mouse, media)
- `src/display/` — LovyanGFX display logic
- `src/storage/` — SD/MSC mounting and payload management
- `src/webui/` — Captive portal, API, and live interface
- `include/config.h` — Pin definitions and build flags per board

---

## 📒 Supported DuckyScript Syntax

### 🔒 DuckyScript v1

```
STRING Hello
ENTER
DELAY 100
```

### 🌐 v2 Additions

```
DEFAULT_CHAR_DELAY 5
LED_R
ATTACKMODE HID STORAGE
```

### 🌟 v3 Features

```
REM_BLOCK
  This is a comment block
END_REM

IF true
  STRING Inside IF
END_IF

FUNCTION greet()
  STRING Hello
RETURN
```

### 🤖 v3+ Exclusive Extensions

```
KEY_PRESS_DELAY 10
DEFAULT_DELAY 100
LOAD_PNG /evil.png
LOAD_JPG /happy.jpg
SET_LAYOUT US
```

---

## 🧰 Example Payload: Evil Google Search

```ds
REM_BLOCK
  Types "Evil Duck" into Google
END_REM

STRING https://www.google.com
ENTER
DELAY 1000
STRING Evil Duck
ENTER
LOAD_PNG /n3wb_main_evil.png
```

---

## 🚀 Flash + Filesystem

### Partitions (16MB devices):

```
# Name       Type   Offset   Size
nvs          data   0x9000   0x6000
otadata      data   0xf000   0x2000
app0         app    0x10000  0x400000
app1         app    0x410000 0x400000
spiffs       data   0x810000 0x700000
```

### Upload Assets:

```bash
pio run --target uploadfs
```

Put your WebUI files, duck images, and favicon in `/data/`.

---

## ⚖ Final Notes

- All settings (`OPT_*`) are runtime-configurable via WebUI
- Only features required for a given board are compiled (`HAS_SD`, `HAS_TFT`, etc.)
- WebUI is dark, fast, and fully mobile-friendly
- All logic is modular; keyboard layouts are stored per-locale and changeable live

---

## 🎓 Credits

Inspired by:

- Hak5 USB Rubber Ducky
- ZeroTrace & ESPKey projects
- USBArmyKnife
- LovyanGFX, AsyncWebServer, ArduinoJson

Developed by: [n3wb](https://github.com/x0SiN0x)

---

## 🚀 Launch Ready

This repo is feature-complete for v1.0.0. Use it as-is, fork it, build payloads, and make ducks do bad things in beautiful ways.

> Need the latest platformio.ini or a ready-to-flash .bin? It's all in this repo.

**Happy Hacking.**

