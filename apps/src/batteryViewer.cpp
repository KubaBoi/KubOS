#include "batteryViewer.h"

BatteryViewer::BatteryViewer() {}

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

void BatteryViewer::draw(DisplayManager *dspMng)
{
    TimeManager *tmmMng = (TimeManager *)mapper->getManager(DSP_MNG);
    if (!tmmMng->isSecond())
        return;

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
        dspMng->printText("    Charging", 10, 40);
    else
        dspMng->printText("Not Charging", 10, 40);

    dspMng->getTFT()->drawNumber(btrMng->getBattVoltage(), 10, 60, 1);
    dspMng->getTFT()->drawNumber(btrMng->getVbusVoltage(), 10, 80, 1);
    dspMng->getTFT()->drawNumber(btrMng->getVbusCurrent(), 10, 100, 1);
}