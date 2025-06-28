#pragma once
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
  LGFX() {
    auto bus = new lgfx::Bus_SPI();
    auto panel = new lgfx::Panel_ST7789();

    lgfx::Bus_SPI::config_t cfg = bus->config();
    cfg.spi_host = SPI3_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 40000000;
    cfg.freq_read = 16000000;
    cfg.spi_3wire = true;
    cfg.use_lock = true;
    cfg.dma_channel = 1;
    cfg.pin_sclk = 6;
    cfg.pin_mosi = 7;
    cfg.pin_miso = -1;
    cfg.pin_dc = 4;
    bus->config(cfg);

    panel->setBus(bus);
    this->setPanel(panel);
  }
};
