#include "app.h"

#ifndef CMD_H
#define CMD_H

class CMD : public App
{
public:
    CMD();

    void rewoke(DisplayManager *dspMng);
    void draw(DisplayManager *dspMng);
};

#endif