#include "config.h"
#include "app.h"

#ifndef WINDOW_H
#define WINDOW_H

class Window : public App
{
public:
    Window();

    void rewoke(DisplayManager *dspMng);
    void draw(DisplayManager *dspMng);
};

#endif