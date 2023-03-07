#include "desktop.h"

Desktop::~Desktop()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->deattachIRQInterrupt(this);
}

void Desktop::start()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->attachIRQInterrupt(this);
}

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

bool Desktop::draw(DisplayManager *dspMng)
{
    for (int i = 29; i > 0; i--)
        dspMng->printText(logger->getLastLog(i + scroll), 0, SCREEN_SIZE - i * 8);
    return false;
}

void Desktop::irqInterrupt(AXP20X_Class *power)
{
    if (power->isPEKShortPressIRQ())
    {
        *syscallmem = 0;
        mapper->newSysCall((uintptr_t)this, SYS_CALL_NEXT, syscallmem);
    }   
}