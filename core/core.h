#include <stdint.h>
#include <vector>

#include "filesystem.h"
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
#include "wifiManager.h"

#include "appObject.h"
#include "app.h"
#include "desktop.h"

#ifndef CORE_H
#define CORE_H

/**
 * Main class initializating managers, mapper, TTGOClass
 * and for managing apps
 * 
 * doc for syscalls is in config/syscalls.h
 */
class Core
{
public:
    /**
     * TTGO and Managers are intialized in constructor
     */
    Core();

    // Update managers
    void updateManagers();

    // Get fileSystem
    FileSystem *getFS();
    // Getter of TTGOClass
    TTGOClass *getTTGO();
    // Getter of ManagerMapper
    ManagerMapper *getMapper();
    // Getter of runningApp
    AppObject *getRunningApp();
    // Find and set runningApp and return found AppObject
    AppObject *setRunningApp(App *app);

    void openDesktop();

    // Start the app
    void startApp(App *app, bool rewoke = true);

    // Rewoke the app
    App *rewokeApp(App *app);
    App *rewokeApp(AppObject *ao);

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
    Desktop *desktop = nullptr;

    FileSystem *fs;
    Logger *logger;
    TTGOClass *ttgo;
    ManagerMapper *mapper;

    uintptr_t syscalls[SYS_CALL_COUNT];

    // Initialization of TTGOClass and turning backlights on
    void initTTGO();
    // Initialization of mapper and managers
    void initManagers();
    // Manage all syscalls
    void manageSysCalls();

    void startDesktop();
    void setupSyscalls();

    static void syscallCLOSE(SysCall *syscall, Core *core);
    static void syscallSTART(SysCall *syscall, Core *core);
    static void syscallNEXT(SysCall *syscall, Core *core);
    static void syscallAPPS(SysCall *syscall, Core *core);
    static void syscallREWOKE(SysCall *syscall, Core *core);
    static void syscallKILL(SysCall *syscall, Core *core);
};

#endif