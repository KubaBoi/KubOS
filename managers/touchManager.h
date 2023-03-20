#include <cmath>

#include "config.h"
#include "manager.h"

#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

/**
 * Class get data of touch of display
 */
class TouchManager : public Manager
{
public:
    TouchManager(ManagerMapper *mappern);

    void update();

    /**
     * Return true if display is touched and fill xn and yn
     * with coordinates of touch
     */
    bool isTouch(int16_t *xn, int16_t *yn);
    bool isTouch();

    /**
     * Return true if display is dragged and fill xn and yn
     * with coordinates of drag vector
    */
    bool isDrag(int16_t *xn, int16_t *yn, double *dist);

private:
    bool isTch, isDrg = false;
    double distance;
    int16_t x, y, vx, vy; // coordinates of touch and vector of drag
};

#endif