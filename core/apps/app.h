#include "logger.h"
#include "managers.h"
#include "managerMapper.h"

#include "displayManager.h"

#ifndef APP_H
#define APP_H

/**
 * Class for application inheritance
 */
class App
{
public:
    ManagerMapper *mapper;
    Logger *logger;
    uintptr_t *syscallmem;

    // App initialization done by core
    void initApp(ManagerMapper *mappern);

    // App start after initApp
    virtual void start();

    // what should be done before sleep of app
    virtual void sleep();

    /**
     * Rewoke app done by core
     * what should be done when apps are switched
     */
    virtual void rewoke(DisplayManager *dspMng);

    // update of every application
    virtual void update();

    // Update done by app when it is on background
    virtual void updateBackground();

    // Draw of application - return true of LVGL needed
    virtual bool draw(DisplayManager *dspMng);

    // Interrupt functions
    virtual void irqInterrupt(AXP20X_Class *power);
    virtual void rtcInterrupt(PCF8563_Class *rtc);
};

#endif