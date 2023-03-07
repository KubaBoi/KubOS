#include "app.h"

void App::initApp(ManagerMapper *mappern)
{
    mapper = mappern;
    logger = mapper->getLogger();
}

void App::rewoke(DisplayManager *dspMng) {}
void App::update() {}
void App::updateBackground() {}
bool App::draw(DisplayManager *dspMng) {}
void App::irqInterrupt(AXP20X_Class *power) {}
void App::rtcInterrupt(PCF8563_Class *rtc) {}