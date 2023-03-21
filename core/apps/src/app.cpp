#include "app.h"

App::App(const char *namen)
{
    name = namen;
    if (name)
        return;
    
    char *namec = (char*)malloc(LOGGER_LENGTH);
    snprintf(namec, LOGGER_LENGTH, "Unknown 0x%x", this);
    name = (const char*)namec;
}

void App::initApp(ManagerMapper *mappern)
{
    mapper = mappern;
    logger = mapper->getLogger();
    syscallmem = (uintptr_t *)malloc(sizeof(uintptr_t));
    logger->log("0x%x %s", this, name);
}

void App::start() {};
void App::sleep() {};
void App::rewoke() {}
void App::update() {}
void App::updateBackground() {}
bool App::draw(DisplayManager *dspMng) {}
void App::irqInterrupt(AXP20X_Class *power) {}
void App::rtcInterrupt(PCF8563_Class *rtc) {}