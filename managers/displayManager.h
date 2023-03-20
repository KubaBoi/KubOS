#include <string.h>
#include <stdarg.h>

#include "config.h"
#include "colors.h"

#include "manager.h"
#include "managerMapper.h"

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

struct fnt
{
    uint16_t color, bgColor;
    uint8_t size, font;
};

/**
 * Class controlling simple GUI
 * colors are defined in config/colors.h
 */
class DisplayManager : public Manager
{
public:
    DisplayManager(ManagerMapper *managern);
    ~DisplayManager();

    // Return pointer to TFT
    TFT_eSPI *getTFT();
    // Return pointer to defaultFont
    fnt *getDefaultFont();
    // Reseter of default font
    void resetDefaultFont();

    // Setter for default background
    void setBGColor(uint16_t bgColor);
    // Setter for default color
    void setColor(uint16_t color);
    // Setter for default size
    void setSize(uint8_t size);
    // Setter for default font
    void setFont(uint8_t font);
    // Setter for default font as fnt struct
    void setDefaultFont(fnt *font);

    // Return value of color rgb888 -> rgb565
    uint16_t getRGB(uint8_t red, uint8_t green, uint8_t blue);

    // Clear display with backgroundColor
    void clear();

    // Print text at coordinates x, y with values
    void printText(const char *text, byte x, byte y, ...);

    // Print text as format with parameters defined in font with values
    void printText(const char *text, byte x, byte y, fnt *font, ...);
    void printText(const char *text, byte x, byte y, fnt *font, va_list values);

private:
    TFT_eSPI *tft;
    fnt *defaultFont; // default font which is used
    fnt *deffnt;      // pointer to defaultFont address
};

#endif