#include <ESPAsyncWebServer.h>
#include "api_live.hpp"
#include "../usb/usb_hid_keyboard.hpp"
#include "../usb/usb_hid_mouse.hpp"

void init_live_routes(AsyncWebServer &server) {
  server.on("/live/key", HTTP_POST, [](AsyncWebServerRequest *req){}, NULL,
    [](AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
      String payload = String((char*)data).substring(0, len);
      if (payload.indexOf("CTRL") >= 0) send_hid_key_combo("CTRL");
      else if (payload.indexOf("ENTER") >= 0) send_hid_key("ENTER");
      req->send(200, "text/plain", "OK");
    });

  server.on("/live/text", HTTP_POST, [](AsyncWebServerRequest *req){}, NULL,
    [](AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
      String text = String((char*)data).substring(0, len);
      text.replace("{"text":"", ""); text.replace(""}", "");
      send_hid_string(text.c_str());
      req->send(200, "text/plain", "OK");
    });

  server.on("/live/mouse", HTTP_POST, [](AsyncWebServerRequest *req){}, NULL,
    [](AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
      String json = String((char*)data).substring(0, len);
      int dx = json.indexOf("dx") >= 0 ? json.substring(json.indexOf("dx")+4).toInt() : 0;
      int dy = json.indexOf("dy") >= 0 ? json.substring(json.indexOf("dy")+4).toInt() : 0;
      send_mouse_move(dx, dy);
      req->send(200, "text/plain", "OK");
    });
}
