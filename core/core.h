#include <stdint.h>
#include <vector>

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
    // Manage all syscalls
    void manageSysCalls();

    // Getter of TTGOClass
    TTGOClass *getTTGO();
    // Getter of ManagerMapper
    ManagerMapper *getMapper();
    // Getter of runningApp
    AppObject *getRunningApp();
    // Find and set runningApp and return found AppObject
    AppObject *setRunningApp(App *app);

    // Start the app
    void startApp(App *app, bool rewoke = true);

    // Close running app and set prev app as running
    void closeApp();

    // Update active app
    void updateApps();

    // Update all apps even if they are on backgound
    void updateBackground();

    // Draw active app
    void drawApps();

    void nextApp();
    void prevApp();

private:
    AppObject *runningApp = nullptr;

    TTGOClass *ttgo;
    ManagerMapper *mapper;
    Logger *logger;

    uintptr_t syscalls[SYS_CALL_COUNT];

    void startDesktop();
    void setupSyscalls();

    /**
     * Close app
     * SYS_CALL_CLOSE
     * <- memory = address of App which should be closed
     * -> return address of runningApp after procedure
     */
    static void syscallCLOSE(SysCall *syscall, Core *core);

    /**
     * Start app
     * SYS_CALL_START
     * <- memory = address of new instance of an App
     * -> return address of runningApp after procedure
     */
    static void syscallSTART(SysCall *syscall, Core *core);

    /**
     * Next app
     * SYS_CALL_NEXT
     * <- memory = if 0 then next if anything else then prev
     * -> return address of runningApp after procedure
     */
    static void syscallNEXT(SysCall *syscall, Core *core);
    static void syscallAPPS(SysCall *syscall, Core *core);
};

#endif