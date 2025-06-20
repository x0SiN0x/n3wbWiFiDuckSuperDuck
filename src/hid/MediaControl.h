#ifndef MEDIA_CONTROL_H
#define MEDIA_CONTROL_H

#include <Arduino.h>

class MediaControl {
public:
  void send(const String& command);
};

#endif