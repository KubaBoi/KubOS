#include <math.h>

#include "app.h"
#include "colors.h"
#include "timeManager.h"

#ifndef CLOCK_H
#define CLOCK_H

class Clock : public App
{
public:
    Clock();

    void rewoke(DisplayManager *dspMng);
    void draw(DisplayManager *dspMng);

private:
    void getAngles(uint8_t minute, uint8_t length, int32_t *x, int32_t *y, uint8_t base=60);
    int32_t x = WINDOW_WIDTH / 2;
    int32_t y = WINDOW_HEIGHT / 2;
    uint32_t r = x - 10;
    uint32_t rl = 2 * (r / 3);
    uint32_t rs = r / 2;

    int32_t olds[6] = {x,y,x,y,x,y}; // array of old ends of hands
    uint8_t forceDraw = 1;
};

#endif