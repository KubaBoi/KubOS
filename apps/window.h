#include "config.h"
#include "app.h"

#ifndef WINDOW_H
#define WINDOW_H

class Window : public App
{
public:
    void rewoke();
    bool draw(DisplayManager *dspMng);
};

#endif