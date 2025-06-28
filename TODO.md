# n3wbWiFiDuckSuperDuck — TODO Tracker

This file tracks outstanding feature work and planned enhancements for the project.

---

## ✅ Completed Features
- DuckyScript v1, v2, v3, and 3+ parsing and runtime
- WebUI with editor, config, about pages
- USB HID (keyboard, mouse, media)
- SD card + internal FS payload loading
- MSC support
- Layout manager with locale keymaps
- Image display on TFT (static)

---

## ⚠️ Incomplete / Partially Implemented

### 1. Bluetooth HID
- [ ] Implement full Bluetooth HID backend
- [ ] Integrate with `bt_hid.cpp` (currently empty)
- [ ] Support toggle/config in WebUI

### 2. Captive Portal
- [ ] Add DNS hijack for captive portal
- [ ] Force redirect all HTTP to `/`
- [ ] Improve AP behavior with timeout auto-reconnect

### 3. HID/MSC Runtime Toggle
- [x] Supported via `ATTACKMODE` in DuckyScript
- [ ] Expose via WebUI toggle
- [ ] Store in NVS and auto-apply on boot

### 4. Layout Selector in WebUI
- [ ] Add dropdown list in config UI (`US`, `UK`, `DE`, `FR`)
- [ ] POST selected layout to `/config`
- [ ] Call `layout_manager.setLayout(...)`

### 5. TFT Status Switching
- [ ] In `vm.cpp`, call `draw_image("n3wb_main_evil.png")` on payload start
- [ ] Revert to `"n3wb_main.png"` on payload complete

### 6. Payload Fallback FS
- [ ] If SD is missing, fallback to SPIFFS for payload discovery
- [ ] Abstract FS logic via `fs::FS &fs = ...`

---

## 💡 Future Enhancements

### OTA Updates
- [ ] Add support for OTA firmware update
- [ ] WebUI-based upload

