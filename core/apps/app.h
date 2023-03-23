#include "logger.h"
#include "managers.h"
#include "managerMapper.h"

#include "displayManager.h"

#ifndef APP_H
#define APP_H

#define SELF_APP (uintptr_t)lv_obj_get_user_data(obj)
#define SELF_APP_ADDR (lv_obj_user_data_t)this

/**
 * Class for application inheritance
 */
class App
{
public:
    ManagerMapper *mapper;
    Logger *logger;
    uintptr_t *syscallmem;

    lv_obj_t *screen = nullptr;
    const char *name;

    App(const char *namen = nullptr, bool needScreen = true);

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
    virtual void rewoke();

    // update of every application
    virtual void update();

    // Update done by app when it is on background
    virtual void updateBackground();

    /*
     * Draw of application
     * return false if app want to draw itself
     * return true if app want to desktop (log) draw
     * 
     * if `screen` of app is not nullptr 
     * this function would not be called
     */
    virtual bool draw(DisplayManager *dspMng);

    // Interrupt functions
    virtual void irqInterrupt(AXP20X_Class *power);
    virtual void rtcInterrupt(PCF8563_Class *rtc);
};

#endif