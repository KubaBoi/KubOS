#include "config.h"
#include "managerMapper.h"

#ifndef APP_H
#define APP_H

/**
 * Class for application inheritance
*/
class App
{
public:
    App(ManagerMapper *mappern);

private:
    ManagerMapper *mapper;
};

#endif