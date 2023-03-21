#include "app.h"

#include <iostream>

#include "batteryManager.h"
#include "timeManager.h"
#include "displayManager.h"

#ifndef BATTERY_VIEWER_H
#define BATTERY_VIEWER_H

class BatteryViewer : public App
{
public:
    BatteryViewer();
    ~BatteryViewer();

    void start();
    void rewoke();
    bool draw(DisplayManager *dspMng);

    void irqInterrupt(AXP20X_Class *power);

private:
    fnt *font = nullptr;
    uint8_t percOld = 0;
};

#endif