#include "config.h"
#include "manager.h"
#include "managerMapper.h"

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

/**
 * Class controlling simple GUI
 */
class DisplayManager : public Manager
{
public:
    DisplayManager(ManagerMapper *managern);

    /**
     * Return pointer to TFT
     */
    TFT_eSPI *getTFT();

    /**
     * Set background color
     */
    void setBGColor(uint16_t bgColor);

    /**
     * Return value of color
     */
    uint16_t getRGB(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * Clear display with backgroundColor
     */
    void clear();

    /**
     * Print text with color
     * at coordinates x, y
     */
    void printText(char *text, byte x, byte y, uint16_t color);

    /**
     * Print text with color and bgColor
     * at coordinates x, y
     */
    void printText(char *text, byte x, byte y, uint16_t color, uint16_t bgColor);

private:
    TFT_eSPI *tft;
    uint16_t backgroundColor = 0x0000;
};

#endif