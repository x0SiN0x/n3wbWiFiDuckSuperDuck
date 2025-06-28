#pragma once
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
    LGFX() {
        auto bus = new lgfx::Bus_SPI();
        {
            auto cfg = bus->config();
            cfg.spi_host = VSPI_HOST;
            cfg.pin_sclk = DISPLAY_SCLK;
            cfg.pin_mosi = DISPLAY_MOSI;
            cfg.pin_miso = DISPLAY_MISO;
            cfg.pin_ss = DISPLAY_CS;
            bus->config(cfg);
        }
        this->setBus(bus);

        auto panel = new lgfx::Panel_ST7735S();
        {
            auto cfg = panel->config();
            cfg.pin_cs = DISPLAY_CS;
            cfg.pin_rst = DISPLAY_RST;
            cfg.pin_busy = DISPLAY_BUSY;
            cfg.pin_dc = DISPLAY_DC;
            cfg.memory_width = DISPLAY_WIDTH;
            cfg.memory_height = DISPLAY_HEIGHT;
            cfg.panel_width = TFT_WIDTH;
            cfg.panel_height = TFT_HEIGHT;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            panel->config(cfg);
        }
        this->setPanel(panel);
    }
};
