#include <stdint.h>

#include "config.h"
#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"

#ifndef CORE_H
#define CORE_H

/**
 * Main class initializating managers, mapper
 * and TTGOClass
 */
class Core
{
public:
    Core();

    void initTTGO();
    void initManagers();

    TTGOClass *getTTGO();
    ManagerMapper *getMapper();

private:
    TTGOClass *ttgo;
    ManagerMapper *mapper;
};

#endif