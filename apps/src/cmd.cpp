#include "cmd.h"

CMD::CMD() {}

void CMD::rewoke(DisplayManager *dspMng)
{
    dspMng->resetDefaultFont();
    dspMng->clear();
}

void CMD::draw(DisplayManager *dspMng)
{
    for (byte i = 0; i < 20; i++)
    {
        dspMng->printText(logger->getLastLog(i), 0, SCREEN_SIZE - ((i+1) * 10));
    }
}