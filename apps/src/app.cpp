#include "app.h"

void App::initApp(ManagerMapper *mappern)
{
    mapper = mappern;
    logger = mapper->getLogger();
}

void App::rewoke(DisplayManager *dspMng) {}
void App::update() {}
void App::updateBackground() {}
void App::draw(DisplayManager *dspMng) {}