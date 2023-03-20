#include "batteryViewer.h"

BatteryViewer::~BatteryViewer()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->deattachIRQInterrupt(this);

    if (font)
        delete font;
}

void BatteryViewer::start()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->attachIRQInterrupt(this);
}

void BatteryViewer::rewoke(DisplayManager *dspMng)
{
    if (!font)
    {
        font = (fnt *)malloc(sizeof(fnt));
        font->bgColor = GREEN_16;
        font->color = BLUE_16;
        font->font = 1;
        font->size = 2;
    }
    dspMng->setDefaultFont(font);
    dspMng->clear();
}

bool BatteryViewer::draw(DisplayManager *dspMng)
{
    TimeManager *tmmMng = (TimeManager *)mapper->getManager(DSP_MNG);
    if (!tmmMng->isSecond())
        return false;

    BatteryManager *btrMng = (BatteryManager *)mapper->getManager(BTR_MNG);
    if (percOld != btrMng->getPercentage())
    {
        percOld = btrMng->getPercentage();
        uint8_t rgb = percOld * 2.55;
        font->bgColor = dspMng->getRGB(255 - rgb, rgb, 0);
        dspMng->setDefaultFont(font);
        dspMng->clear();
    }

    dspMng->getTFT()->drawNumber(btrMng->getPercentage(), 10, 10, 1);

    if (btrMng->isCharging())
        dspMng->printText("Charging", 10, 40);
    
    dspMng->getTFT()->drawNumber(btrMng->getBattVoltage(), 10, 60, 1);
    dspMng->getTFT()->drawNumber(btrMng->getVbusVoltage(), 10, 80, 1);
    dspMng->getTFT()->drawNumber(btrMng->getVbusCurrent(), 10, 100, 1);
    return false;
}

void BatteryViewer::irqInterrupt(AXP20X_Class *power)
{
    if (power->isVbusPlugInIRQ())
    {
        *syscallmem = (uintptr_t)this;
        mapper->newSysCall((uintptr_t)this, SYS_CALL_REWOKE, syscallmem);
    }
}