#include <stdlib.h> 

#include "app.h"
#include "touchManager.h"

#ifndef GAY_METER_H
#define GAY_METER_H

class GayMeter : public App
{
public:
    void rewoke(DisplayManager *dspMng);
    void update();
    bool draw(DisplayManager *dspMng);
private:
    uint8_t gayValue;
};

#endif