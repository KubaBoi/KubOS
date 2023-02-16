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

    /**
     * Return true if display is touched and fill xn and yn
     * with coordinates of touch
     */
    bool isTouch(int16_t *xn, int16_t *yn);

    // Return last touch `x` coordinate
    int16_t getLastX();
    // Return last touch `y` coordinate
    int16_t getLastY();

private:
    int16_t x, y; // coordinates of touch
};

#endif