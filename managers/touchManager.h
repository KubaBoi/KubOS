#include "config.h"
#include "manager.h"

#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

class TouchManager : public Manager
{
public:
    TouchManager(ManagerMapper *mappern);
    void update();

    bool isTouch(int16_t *xn, int16_t *yn);
    int16_t getLastX();
    int16_t getLastY();

private:
    int16_t x, y;
};

#endif