#include <stdint.h>

#include "logger.h"
#include "config.h"
#include "managerMapper.h"
#include "irqManager.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"
#include "displayManager.h"
#include "alarmManager.h"

#include "appObject.h"
#include "app.h"
#include "desktop.h"

#ifndef CORE_H
#define CORE_H

/**
 * Main class initializating managers, mapper, TTGOClass
 * and for managing apps
 */
class Core
{
public:
    /**
     * TTGO and Managers are intialized in constructor
     */
    Core();

    // Initialization of TTGOClass and turning backlights on
    void initTTGO();
    // Initialization of mapper and managers
    void initManagers();
    // Update managers
    void updateManagers();

    // Getter of TTGOClass
    TTGOClass *getTTGO();
    // Getter of ManagerMapper
    ManagerMapper *getMapper();

    // Start the app
    void startApp(App *app, bool rewoke = true);

    // Close running app and set prev app as running
    void closeApp();

    // Update all apps
    void updateApps();

    // Update all apps even if they are on backgound
    void updateBackground();

    // Draw all apps
    void drawApps();

    void nextApp();

private:
    AppObject *runningApp = nullptr;

    TTGOClass *ttgo;
    ManagerMapper *mapper;
    Logger *logger;

    int8_t scroll;

    void startDesktop();
};

#endif