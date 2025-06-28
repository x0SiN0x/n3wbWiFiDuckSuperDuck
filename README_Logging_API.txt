# Web Console Logging API

Use `log()` and `logln()` instead of `Serial.print()` and `Serial.println()` for mirrored logging.

- `log("Message")` → appends to buffer and sends to Serial
- `logln("Message")` → appends + newline to buffer and Serial

These automatically appear on the Web Console (`console.html`).
