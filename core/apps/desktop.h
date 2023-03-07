#include "app.h"
#include "touchManager.h"

#ifndef DESKTOP_H
#define DESKTOP_H

class Desktop : public App
{
public:
    void rewoke(DisplayManager *dspMng);
    void update();
    bool draw(DisplayManager *dspMng);
private:
    uint8_t scroll;
};

#endif