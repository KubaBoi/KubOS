#include "app.h"
#include "touchManager.h"
#include "irqManager.h"
#include "config.h"
#include "colors.h"

#ifndef DESKTOP_H
#define DESKTOP_H

/**
 * Class for desktop
 * this app will be always started and controll
 * main IO operations of watches
 * (swaping applications etc...)
 */
class Desktop : public App
{
public:
    Desktop();
    ~Desktop();

    void start();

    void rewoke();
    void rewokeOnBc(App *app);
    void update();
    bool draw(DisplayManager *dspMng);

    void irqInterrupt(AXP20X_Class *power);

private:
    int8_t scroll;
    char *appName = nullptr;
    fnt *headerFont;
};

#endif