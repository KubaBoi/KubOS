#include "desktop.h"

void Desktop::rewoke(DisplayManager *dspMng)
{
    dspMng->resetDefaultFont();
	dspMng->clear();
	scroll = 0;
}

void Desktop::update()
{
    TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
    int16_t x, y;
    double dist;
    if (!tchMng->isDrag(&x, &y, &dist))
        return;
    scroll = y / 4;
    if (scroll < 0)
        scroll = 0;
}

void Desktop::draw(DisplayManager *dspMng)
{
    for (int i = 29; i > 0; i--)
        dspMng->printText(logger->getLastLog(i + scroll), 0, SCREEN_SIZE - i * 8);
}