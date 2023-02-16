#include "displayManager.h"

DisplayManager::DisplayManager(ManagerMapper *mappern) : Manager(mappern)
{
    tft = mappern->getTTGO()->tft;
}

TFT_eSPI *DisplayManager::getTFT() { return tft; }

void DisplayManager::setBGColor(uint16_t bgColor)
{
    backgroundColor = bgColor;
}

uint16_t DisplayManager::getRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;
    return (uint16_t) (r | g | b);
}

void DisplayManager::clear()
{
    tft->fillScreen(backgroundColor);
}

void DisplayManager::printText(char *text, byte x, byte y, uint16_t color)
{
}

void DisplayManager::printText(char *text, byte x, byte y, uint16_t color, uint16_t bgColor)
{
}
