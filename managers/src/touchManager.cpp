#include "touchManager.h"

TouchManager::TouchManager(ManagerMapper *mappern) : Manager(mappern) 
{
    logger->log("...Touch Manager");
}

bool TouchManager::isTouch(int16_t *xn, int16_t *yn)
{
    bool ret = mapper->getTTGO()->getTouch(x, y);
    *xn = x;
    *yn = y;
    return ret;
}

int16_t TouchManager::getLastX() { return x; }

int16_t TouchManager::getLastY() { return y; }