#include "app.h"

void App::initApp(ManagerMapper *mappern)
{
    mapper = mappern;
    logger = mapper->getLogger();
}

void App::update() {}
void App::draw(DisplayManager *dspMng) {}