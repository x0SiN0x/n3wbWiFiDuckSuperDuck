
#pragma once
#include <string>

void send_hid_key(const std::string& key);
void send_hid_string(const std::string& text);
void send_mouse_move(int dx, int dy);
