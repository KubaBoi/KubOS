#include <stdlib.h> 

#include "app.h"
#include "touchManager.h"

#ifndef GAY_METER_H
#define GAY_METER_H

class GayMeter : public App
{
public:
    GayMeter();

    void rewoke();
private:
    uint8_t gayValue;

    static void click(lv_obj_t *obj, lv_event_t event);
};

#endif