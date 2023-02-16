#include "cmd.h"

CMD::CMD() {}

void CMD::update()
{
}

void CMD::draw(DisplayManager *dspMng)
{
    dspMng->clear();
    for (byte i = 0; i < 20; i++)
    {
        dspMng->printText(logger->getLastLog(i), 0, i * 10);
    }
}