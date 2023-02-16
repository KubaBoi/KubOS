#include "displayManager.h"

DisplayManager::DisplayManager(ManagerMapper *mappern) : Manager(mappern)
{
    defaultFont.bgColor = BLACK_16;
    defaultFont.textColor = WHITE_16;
    defaultFont.size = 5;
    defaultFont.font = 1; 
    deffnt = defaultFont;

    tft = mappern->getTTGO()->tft;
	ttgo->tft->fillScreen(backgroundColor);
}

DisplayManager::~DisplayManager() { delete(deffnt); }

TFT_eSPI *DisplayManager::getTFT() { return tft; }
fnt *DisplayManager::getDefaultFont() { return defaultFont; }
void DisplayManager::resetDefaultFont() { setDefaultFont(deffnt); }

void DisplayManager::setBGColor(uint16_t bgColor) { defaultFont.bgColor = bgColor; }
void DisplayManager::setColor(uint16_t color) { defaultFont.textColor = color; }
void DisplayManager::setSize(uint8_t size) { defaultFont.textColor = color; }
void DisplayManager::setFont(uint8_t font) { defaultFont.font = font; }
void DisplayManager::setDefaultFont(fnt *font) { defaultFont = font; }

uint16_t DisplayManager::getRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;
    return (uint16_t) (r | g | b);
}

void DisplayManager::clear()
{
    tft->fillScreen(defaultFont->bgColor);
}

void DisplayManager::printText(char* text, byte x, byte y)
{
    printText(text, x, y, defaultFont);
}

void DisplayManager::printText(char *text, byte x, byte y, uint16_t color, uint8_t size)
{
    tft->setTextColor(color);
    tft->drawString(text, x, y, defaultFont);
}

void DisplayManager::printText(char *text, byte x, byte y, uint16_t color, uint16_t bgColor, uint8_t size)
{
    tft->setTextColor(color);
    tft->drawString(text, x, y, defaultFont);
}

void DisplayManager::printText(char *text, byte x, byte y, fnt font)
{

}
