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

    void initApp(ManagerMapper *mappern);

    // update of every application
    virtual void update();

    // draw of every application
    virtual void draw(DisplayManager *dspMng);
};

#endif