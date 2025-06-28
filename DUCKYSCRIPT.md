# DuckyScript Quick Reference for n3wb WiFiDuckSuperDuck

This reference replicates the official DuckyScript style found at https://docs.hak5.org, but includes all enhancements supported by the n3wb WiFiDuckSuperDuck firmware, including exclusive v3+ commands.

---

## REMARKS

### REM (v1)
Adds a single-line comment. Ignored by the parser.
```ds
REM This is a comment
```

### REM_BLOCK / END_REM (v3)
Marks a multi-line comment block.
```ds
REM_BLOCK
  This is a multi-line comment block
  It will be ignored by the interpreter
END_REM
```

---

## KEYSTROKE INJECTION

### STRING (v1)
The `STRING` command keystroke injects (types) a series of characters. Uppercase characters will automatically press SHIFT as needed. Trailing spaces are ignored.
```ds
STRING Hello World!
```

### STRINGLN (v3)
Same as `STRING`, but automatically appends an `ENTER` keystroke.
```ds
STRINGLN Hello with ENTER
```

### KEY NAMES (v1)
Simulate single keypresses directly.
```ds
ENTER
TAB
ESCAPE
UPARROW
DOWNARROW
LEFTARROW
RIGHTARROW
DELETE
BACKSPACE
```

### COMBO KEYS (v1)
Allows pressing multiple keys simultaneously, such as modifiers and a regular key.
```ds
CTRL ALT DELETE
CTRL SHIFT ESCAPE
GUI r
```

### HOLD / RELEASE (v3)
Explicitly hold a modifier or key until released manually.
```ds
HOLD CTRL
STRING a
RELEASE CTRL
```

### REPEAT (v1)
Repeats the last executed instruction N times.
```ds
REPEAT 5
```

---

## TIMING

### DELAY (v1)
Pauses execution for a number of milliseconds.
```ds
DELAY 1000
```

### DEFAULT_DELAY (v1)
Applies a delay automatically after every instruction line.
```ds
DEFAULT_DELAY 200
```

### DEFAULT_CHAR_DELAY (v2)
Adds a delay between each character in STRING injections.
```ds
DEFAULT_CHAR_DELAY 20
```

### KEY_PRESS_DELAY (v3+)
Adds a delay between keypresses in combo key instructions.
```ds
KEY_PRESS_DELAY 10
```

### JITTER (v3)
Adds a random ± millisecond variation to subsequent delays.
```ds
JITTER 50
```

---

## DISPLAY CONTROL (v3+)
Display commands are only active on boards with HAS_TFT defined.

### LOAD_PNG
Loads and displays a PNG file from flash or SD on the TFT.
```ds
LOAD_PNG /n3wb_main.png
```

### LOAD_JPG
Loads and displays a JPG file.
```ds
LOAD_JPG /evil_duck.jpg
```

---

## BUTTON & LED (v2/v3)
Control onboard buttons and addressable LEDs.
```ds
WAIT_FOR_BUTTON_PRESS     ; Pause until button is pressed
LED_R                     ; Red LED
LED_G                     ; Green LED
LED_B                     ; Blue LED
LED_OFF                   ; Turn off LED
DISABLE_BUTTON            ; Disable input from onboard button
ENABLE_BUTTON             ; Re-enable input from onboard button
```

---

## USB MODE & ATTACKMODES (v2/v3)
Switch between supported USB personas (HID, STORAGE, or both).
```ds
ATTACKMODE HID
ATTACKMODE STORAGE
ATTACKMODE HID STORAGE
SAVE_ATTACKMODE            ; Save current mode to stack
RESTORE_ATTACKMODE         ; Restore previously saved mode
```

---

## VARIABLES & CONSTANTS (v3)
Define and use constants or expressions.
```ds
DEFINE MAX_ATTEMPTS 5
VAR counter = 0
VAR status = (counter < MAX_ATTEMPTS)
```
Operators: `+ - * / % << >> & | ^`, logical AND/OR, comparison, etc.

---

## CONTROL FLOW (v3)
Structured logic blocks for conditionals and loops.
```ds
IF counter > 0
  STRING Count valid
ELSE
  STRING Count invalid
END_IF

WHILE counter < 5
  STRING Looping
  VAR counter = counter + 1
END_WHILE

FUNCTION hello()
  STRING Hello World
RETURN
```

---

## PAYLOAD CONTROL (v3)
Control how and when payloads run.
```ds
RESTART_PAYLOAD           ; Restart current script
STOP_PAYLOAD              ; Stop execution immediately
RESET                     ; Reboot device
```

---

## ADVANCED (v3/v3+)
Advanced controls for conditional triggers and dynamic logic.
```ds
HIDE_PAYLOAD              ; Hide payload from listing (future use)
WAIT_FOR_LOCK_ON CAPS     ; Wait until caps lock is on
WAIT_FOR_LOCK_OFF CAPS    ; Wait until caps lock is off
RANDOM_INT var 1 100      ; Assign random integer to var
SET_LAYOUT US             ; Switch keyboard layout
```

---

## EXCLUSIVE v3+ COMMANDS

| Command              | Description                            |
|---------------------|----------------------------------------|
| SET_LAYOUT <layout> | Switch keyboard layout at runtime      |
| LOAD_PNG <file>     | Show PNG image on TFT display          |
| LOAD_JPG <file>     | Show JPG image on TFT display          |
| KEY_PRESS_DELAY <n> | Millisecond delay between combo keys   |
| DEFAULT_DELAY <n>   | Delay after every instruction line     |

---

## NOTES

- All delays are in milliseconds and capped at 32767
- Layout options: US, UK, DE, FR, etc.
- DuckyScript file extension is `.ds`
- Files are stored in `/payloads/` on internal flash or SD card

---

**Firmware: n3wb WiFiDuckSuperDuck**  
**Syntax: DuckyScript v1, v2, v3, and v3+**

