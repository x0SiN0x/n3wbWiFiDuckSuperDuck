# n3wb WiFiDuckSuperDuck

## INSTRUCTIONS.md: DuckyScript Command Reference

This document provides a full reference for writing DuckyScript for use with the n3wb WiFiDuckSuperDuck firmware. The syntax is based on official Hak5 DuckyScript v1, v2, v3, with additional exclusive v3+ extensions designed for this firmware.

> 📘 Refer to [https://docs.hak5.org/hak5-usb-rubber-ducky/duckyscript-quick-reference/](https://docs.hak5.org/hak5-usb-rubber-ducky/duckyscript-quick-reference/) for Hak5’s original syntax.

---

## 🧠 Supported Syntax Versions

| Version | Description                                |
| ------- | ------------------------------------------ |
| v1      | Classic DuckyScript (ENTER, DELAY, STRING) |
| v2      | Bash Bunny & Key Croc extensions           |
| v3      | Structured syntax (IF, WHILE, FUNC)        |
| v3+     | **n3wb-exclusive extensions**              |

---

## 1. 📓 Comments

```ds
REM This is a comment                ; [v1]
REM_BLOCK                           ; [v3]
  Multi-line comment block
END_REM                             ; [v3]
```

---

## 2. ⌨ Keystroke Injection

```ds
STRING Hello world                  ; [v1]
STRINGLN Hello                      ; [v3] (auto ENTER)
<KEYNAME>                           ; [v1] e.g. ENTER, TAB
CTRL ALT DEL                        ; [v1] modifier combos
HOLD CTRL                           ; [v3] hold modifier
RELEASE CTRL                        ; [v3] release modifier
REPEAT 3                            ; [v1] repeat last line 3 times
```

---

## 3. ⏱ Delays & Timing

```ds
DELAY 1000                          ; [v1] wait in ms
DEFAULT_DELAY 200                  ; [v1] delay after every command
DEFAULT_CHAR_DELAY 10              ; [v2] delay between characters
KEY_PRESS_DELAY 10                 ; [v3+] delay inside combo key press
JITTER 10                           ; [v3] random ± jitter
```

---

## 4. 🖼 Display Control (TFT-equipped boards only)

```ds
LOAD_PNG /happy.png                 ; [v3+]
LOAD_JPG /evil.jpg                  ; [v3+]
```

- Images must be present in SPIFFS or SD card
- PNGs support transparency; JPGs for full-res

---

## 5. 🔘 Button & LED

```ds
WAIT_FOR_BUTTON_PRESS              ; [v3]
LED_R                              ; [v2] red LED (if defined)
LED_OFF                            ; [v2] turn off LED
DISABLE_BUTTON                     ; [v3] disables physical button
ENABLE_BUTTON                      ; [v3] re-enables button
```

---

## 6. 🔌 USB Mode Switching

```ds
ATTACKMODE HID                     ; [v2]
ATTACKMODE STORAGE                 ; [v2]
ATTACKMODE HID STORAGE             ; [v2]
SAVE_ATTACKMODE                    ; [v3]
RESTORE_ATTACKMODE                 ; [v3]
```

- HID = Keyboard + Mouse + Media
- STORAGE = USB drive (MSC)

---

## 7. 🧮 Variables, Math, and Constants

```ds
DEFINE MY_DELAY 500                ; [v3] constant
VAR counter = 3                    ; [v3] variable
VAR x = (4 + 2) * 10               ; [v3] expression
```

Operators: `+ - * / % << >> & | ^`, logical AND/OR, comparison, etc.

---

## 8. 🔄 Control Flow

```ds
IF counter > 2                     ; [v3]
  STRING Greater than 2
ELSE
  STRING Not greater
END_IF

WHILE counter < 5                  ; [v3]
  STRING Looping
  VAR counter = counter + 1
END_WHILE

FUNCTION greet()                   ; [v3]
  STRING Hello
RETURN
```

---

## 9. ▶ Payload Management

```ds
RESTART_PAYLOAD                    ; [v3]
STOP_PAYLOAD                       ; [v3]
RESET                              ; [v3] reboots microcontroller
```

---

## 10. 🎛 Advanced + Optional

```ds
HIDE_PAYLOAD                       ; [v3] (future, no-op now)
WAIT_FOR_LOCK_ON CAPS             ; [v3] wait for caps lock on
RANDOM_INT var 1 10               ; [v3] set var to random 1-10
```

---

## 🔥 v3+ Unique Features Summary

| Feature            | Syntax                 | Description                        |
| ------------------ | ---------------------- | ---------------------------------- |
| Key Press Delay    | `KEY_PRESS_DELAY <ms>` | Controls delay between combo keys  |
| Default Line Delay | `DEFAULT_DELAY <ms>`   | Delay added after every command    |
| Layout Switcher    | `SET_LAYOUT <US>`      | Dynamically switch keyboard layout |
| Image Control      | `LOAD_PNG /file.png`   | Show image on TFT                  |
| JPEG Support       | `LOAD_JPG /file.jpg`   | Show JPG image                     |

---

## 🧪 Best Practices

- Cap delays at 32767 ms (firmware-enforced)
- Keep payloads in `/payloads/*.ds` on SPIFFS or SD
- Use `REM_BLOCK` for documenting sections
- Set `DEFAULT_CHAR_DELAY` for more human-like typing

---

## 📘 Resources

- Project: [n3wb WiFiDuckSuperDuck on GitHub](https://github.com/x0SiN0x/n3wbWiFiDuckSuperDuck)
- Hak5 DuckyScript Docs: [https://docs.hak5.org/hak5-usb-rubber-ducky/duckyscript-quick-reference](https://docs.hak5.org/hak5-usb-rubber-ducky/duckyscript-quick-reference)

---

**Happy injecting!**

