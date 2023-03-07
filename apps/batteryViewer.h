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

    void rewoke(DisplayManager *dspMng);
    bool draw(DisplayManager *dspMng);

private:
    fnt *font = nullptr;
    uint8_t percOld = 0;
};

#endif