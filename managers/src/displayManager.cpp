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
    tft->fillScreen(BLACK_16);
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

void DisplayManager::clear() { tft->fillScreen(defaultFont->bgColor); }

void DisplayManager::printText(const char *text, byte x, byte y, ...) 
{ 
    va_list values;
    va_start(values, y);
    printText(text, x, y, defaultFont, values); 
}

void DisplayManager::printText(const char *text, byte x, byte y, fnt *font, ...)
{
    va_list values;
    va_start(values, font);
    printText(text, x, y, font, values);
}

void DisplayManager::printText(const char *text, byte x, byte y, fnt *font, va_list values)
{
    char *prepstr = (char *)malloc(LOGGER_MAX_LENGTH);
    vsnprintf(prepstr, LOGGER_MAX_LENGTH, text, values);
    tft->setTextColor(font->color, font->bgColor);
    tft->setTextSize(font->size);
    tft->drawString(prepstr, x, y, font->font);
    delete prepstr;
}
