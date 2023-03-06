#include "displayManager.h"

DisplayManager::DisplayManager(ManagerMapper *mappern) : Manager(mappern, "DSP")
{
    defaultFont = (fnt *)malloc(sizeof(fnt));
    defaultFont->bgColor = BLACK_16;
    defaultFont->color = WHITE_16;
    defaultFont->size = 1;
    defaultFont->font = 1;
    deffnt = defaultFont;
    tft = mappern->getTTGO()->tft;
}

DisplayManager::~DisplayManager() { delete (deffnt); }

TFT_eSPI *DisplayManager::getTFT() { return tft; }
fnt *DisplayManager::getDefaultFont() { return defaultFont; }
void DisplayManager::resetDefaultFont() { setDefaultFont(deffnt); }

void DisplayManager::setBGColor(uint16_t bgColor) { defaultFont->bgColor = bgColor; }
void DisplayManager::setColor(uint16_t color) { defaultFont->color = color; }
void DisplayManager::setSize(uint8_t size) { defaultFont->size = size; }
void DisplayManager::setFont(uint8_t font) { defaultFont->font = font; }
void DisplayManager::setDefaultFont(fnt *font) { defaultFont = font; }

uint16_t DisplayManager::getRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;
    return (uint16_t)(r | g | b);
}

void DisplayManager::clear()
{
    tft->fillScreen(defaultFont->bgColor);
}

void DisplayManager::printText(char *text, byte x, byte y)
{
    printText(text, x, y, defaultFont);
}

void DisplayManager::printText(char *text, byte x, byte y, fnt *font)
{
    tft->setTextColor(font->color, font->bgColor);
    tft->setTextSize(font->size);
    tft->drawString(text, x, y, font->font);
}
