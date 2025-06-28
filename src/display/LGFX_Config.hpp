
#pragma once
#include <LovyanGFX.hpp>

#ifndef DISPLAY_SCLK
#define DISPLAY_SCLK 6
#endif
#ifndef DISPLAY_MOSI
#define DISPLAY_MOSI 7
#endif
#ifndef DISPLAY_MISO
#define DISPLAY_MISO -1
#endif
#ifndef DISPLAY_CS
#define DISPLAY_CS -1
#endif
#ifndef DISPLAY_DC
#define DISPLAY_DC 4
#endif
#ifndef DISPLAY_RST
#define DISPLAY_RST -1
#endif
#ifndef DISPLAY_LEDA
#define DISPLAY_LEDA -1
#endif
#ifndef DISPLAY_BUSY
#define DISPLAY_BUSY -1
#endif
#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH 240
#endif
#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT 135
#endif

class LGFX : public lgfx::LGFX_Device {
public:
  LGFX() {
    auto bus = new lgfx::Bus_SPI();
    auto panel = new lgfx::Panel_ST7789();

    {
      auto cfg = bus->config();
      cfg.spi_host = SPI3_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read = 16000000;
      cfg.spi_3wire = true;
      cfg.use_lock = true;
      cfg.dma_channel = 1;
      cfg.pin_sclk = DISPLAY_SCLK;
      cfg.pin_mosi = DISPLAY_MOSI;
      cfg.pin_miso = DISPLAY_MISO;
      cfg.pin_dc = DISPLAY_DC;
      bus->config(cfg);
    }

    panel->setBus(bus);  // ✅ correctly assign the SPI bus to the panel

    {
      auto cfg = panel->config();
      cfg.pin_cs = DISPLAY_CS;
      cfg.pin_rst = DISPLAY_RST;
      cfg.pin_busy = DISPLAY_BUSY;
      cfg.panel_width = DISPLAY_WIDTH;
      cfg.panel_height = DISPLAY_HEIGHT;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      panel->config(cfg);
    }

    this->setPanel(panel);
  }
};
