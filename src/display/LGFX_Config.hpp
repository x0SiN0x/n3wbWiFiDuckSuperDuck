#pragma once
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
    LGFX() {
        auto bus = new lgfx::Bus_SPI();
        bus->config.spi_host = VSPI_HOST;

#ifdef DISPLAY_SCLK
        bus->config.pin_sclk = DISPLAY_SCLK;
#endif
#ifdef DISPLAY_MOSI
        bus->config.pin_mosi = DISPLAY_MOSI;
#endif
#ifdef DISPLAY_MISO
        bus->config.pin_miso = DISPLAY_MISO;
#endif
#ifdef DISPLAY_CS
        bus->config.pin_ss = DISPLAY_CS;
#endif

        this->setBus(bus);

        auto panel = new lgfx::Panel_ST7735S(); // Change for other TFTs
        panel->config.pin_cs   = DISPLAY_CS;
        panel->config.pin_rst  = DISPLAY_RST;
        panel->config.pin_busy = DISPLAY_BUSY;
        panel->config.pin_dc   = DISPLAY_DC;
        panel->config.memory_width  = DISPLAY_WIDTH;
        panel->config.memory_height = DISPLAY_HEIGHT;
        panel->config.panel_width   = TFT_WIDTH;
        panel->config.panel_height  = TFT_HEIGHT;
        panel->config.offset_x = 0;
        panel->config.offset_y = 0;

        this->setPanel(panel);
    }
};

// Declare external draw function
void draw_image(LGFX& tft, const char* path);
