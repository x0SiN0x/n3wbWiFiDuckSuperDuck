
#pragma once
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
  LGFX() {
    auto bus = new lgfx::Bus_SPI();

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
      cfg.pin_dc   = DISPLAY_DC;
      bus->config(cfg);
    }

    // ----- Panel selection based on build flag -----
    lgfx::Panel_Device* panel = nullptr;

    #if defined(TFT_PANEL_ST7735)
      panel = new lgfx::Panel_ST7735();
    #elif defined(TFT_PANEL_ST7789)
      panel = new lgfx::Panel_ST7789();
    #elif defined(TFT_PANEL_ILI9341)
      panel = new lgfx::Panel_ILI9341();
    #else
      #error "No valid TFT panel defined! Use -DTFT_PANEL_ST7789 or -DTFT_PANEL_ILI9341"
    #endif

    panel->setBus(bus);

    {
      auto cfg = panel->config();
      cfg.pin_cs   = DISPLAY_CS;
      cfg.pin_rst  = DISPLAY_RST;
      cfg.pin_busy = DISPLAY_BUSY;
      cfg.panel_width  = DISPLAY_WIDTH;
      cfg.panel_height = DISPLAY_HEIGHT;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      panel->config(cfg);
    }

    this->setPanel(panel);
  }
};
