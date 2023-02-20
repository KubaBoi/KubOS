#include "touchManager.h"

TouchManager::TouchManager(ManagerMapper *mappern) : Manager(mappern)
{
    logger->log("...Touch Manager");
}

void TouchManager::update()
{
    /*int16_t nx, ny; // new values
    isDrg = false;

    bool nIsTch = mapper->getTTGO()->getTouch(nx, ny);
    if (isTch && nIsTch) // drag
    {
        vx = nx - x;
        vy = ny - y;
        float dist = (vx * vx) + (vy * vy);
        if (dist >= MIN_DRAG_DIST)
            isDrg = true;
    }
    else if (!isTch && nIsTch)
    {
        x = nx;
        y = ny;
        isTch = true;
    }
    else
        isTch = nIsTch;*/
}

bool TouchManager::isTouch(int16_t *xn, int16_t *yn)
{
    bool ret = mapper->getTTGO()->getTouch(x, y);
    *xn = x;
    *yn = y;
    return ret;
}

bool TouchManager::isDrag(int16_t *xn, int16_t *yn)
{
    *xn = vx;
    *yn = vy;
    return isDrg;
}