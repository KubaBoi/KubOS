#include "clock.h"

Clock::Clock() {}

void Clock::rewoke(DisplayManager *dspMng)
{
    dspMng->resetDefaultFont();
    dspMng->clear();
    dspMng->getTFT()->drawCircle(x, y, r, WHITE_16);
    for (uint8_t i = 0; i < 12; i++)
    {
        int32_t xe, ye;
        getAngles(i, r, &xe, &ye, 12);

        if (i % 3 == 0)
            dspMng->getTFT()->drawLine(x, y, x + xe, y + ye, RED_16);
        else
            dspMng->getTFT()->drawLine(x, y, x + xe, y + ye, WHITE_16);
    }
    dspMng->getTFT()->fillCircle(x, y, r - 10, BLACK_16);
    forceDraw = 1;
    draw(dspMng);
    forceDraw = 0;
}

void Clock::draw(DisplayManager *dspMng)
{
    TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);

    if (!tmmMng->isSecond() && !forceDraw)
        return;

    // clear old
    for (uint8_t i = 0; i < 3; i++)
        dspMng->getTFT()->drawLine(x, y, x + olds[i * 2], y + olds[i * 2 + 1], BLACK_16);

    // calc new
    getAngles(tmmMng->getSecond(), rl, &olds[0], &olds[1]);
    getAngles(tmmMng->getMinute(), rl, &olds[2], &olds[3]);
    getAngles((tmmMng->getHour() % 12) * 60 + tmmMng->getMinute(), rs, &olds[4], &olds[5], 12 * 60);

    // draw new
    dspMng->getTFT()->drawLine(x, y, x + olds[0], y + olds[1], WHITE_16);
    dspMng->getTFT()->drawLine(x, y, x + olds[2], y + olds[3], WHITE_16);
    dspMng->getTFT()->drawLine(x, y, x + olds[4], y + olds[5], RED_16);
}

void Clock::getAngles(uint8_t minute, uint8_t length, int32_t *xe, int32_t *ye, uint8_t base)
{
    double radians = (((double)minute / base) * 2 * M_PI) - (M_PI / 2);
    *xe = cos(radians) * length;
    *ye = sin(radians) * length;
}