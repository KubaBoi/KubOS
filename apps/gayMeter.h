#include <stdlib.h>

#include "app.h"
#include "touchManager.h"

#ifndef GAY_METER_H
#define GAY_METER_H

class GayMeter : public App
{
public:
    lv_obj_t *gayLabel, *gayCommLabel;
    uint16_t choosing;

    GayMeter();

    void update();

private:
    static void click(lv_obj_t *obj, lv_event_t event);

    static char comments[10][100];
};

#endif