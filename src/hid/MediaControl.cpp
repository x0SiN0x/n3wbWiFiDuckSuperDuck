#include "hid/MediaControl.h"
#include "BleKeyboard.h" // Or appropriate HID library for media keys

BleKeyboard bleKeyboard;

void MediaControl::send(const String& command) {
  bleKeyboard.begin();
  if (command == "VOLUME_UP") bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  else if (command == "VOLUME_DOWN") bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  else if (command == "MUTE") bleKeyboard.write(KEY_MEDIA_MUTE);
  else if (command == "PLAY_PAUSE") bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  else if (command == "NEXT") bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
  else if (command == "PREVIOUS") bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
  bleKeyboard.end();
}
