#include <stdint.h>

#include "config.h"
#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"
#include "displayManager.h"

#ifndef CORE_H
#define CORE_H

/**
 * Main class initializating managers, mapper
 * and TTGOClass
 */
class Core
{
public:
    /**
     * If `doInitialization` = `true`
     * TTGO and Managers are intialized in constructor
     */
    Core(bool doInitialization = true);

    // Initialization of TTGOClass and turning backlights on
    void initTTGO();
    // Initialization of mapper and managers
    void initManagers();

    // Getter of TTGOClass
    TTGOClass *getTTGO();
    // Getter of ManagerMapper
    ManagerMapper *getMapper();

private:
    TTGOClass *ttgo;
    ManagerMapper *mapper;
};

#endif