#include "touchManager.h"

TouchManager::TouchManager(ManagerMapper *mappern) : Manager(mappern, "TCH")
{
    vx, vy, distance, isTch = 0;
}

void TouchManager::update()
{
    int16_t nx, ny; // new values
    isDrg = false;
    vx, vy = 0;

    bool nIsTch = mapper->getTTGO()->getTouch(nx, ny);
    if (isTch && nIsTch) // drag
    {
        vx = nx - x;
        vy = ny - y;
        distance = sqrt((vx * vx) + (vy * vy));
        if (distance >= MIN_DRAG_DIST)
            isDrg = true;
    }
    else if (!isTch && nIsTch)
    {
        x = nx;
        y = ny;
        isTch = true;
    }
    isTch = nIsTch;
}

bool TouchManager::isTouch(int16_t *xn, int16_t *yn)
{
    *xn = x;
    *yn = y;
    return isTch;
}

bool TouchManager::isTouch() { return isTch; }

bool TouchManager::isDrag(int16_t *xn, int16_t *yn, double *dist)
{
    *xn = vx;
    *yn = vy;
    *dist = distance;
    return isDrg;
}