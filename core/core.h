#include <stdint.h>

#include "logger.h"
#include "config.h"
#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"
#include "displayManager.h"

#include "app.h"

#ifndef CORE_H
#define CORE_H

struct appObject
{
    App *app;
    appObject *next, *prev;
};

/**
 * Main class initializating managers, mapper, TTGOClass
 * and for managing apps
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

    // Start the app
    void startApp(App *app);

    // Close the app
    void closeApp(App *app);

    // Update all apps
    void updateApps();

    // Draw all apps
    void drawApps();

private:
    appObject *runningApps = nullptr;

    TTGOClass *ttgo;
    ManagerMapper *mapper;
    Logger *logger;
};

#endif