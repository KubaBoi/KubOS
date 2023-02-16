#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "manager.h"

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

/**
 * Class gets data from RTC module and serves them as integers
 */
class TimeManager : public Manager
{
public:
    TimeManager(ManagerMapper *managern);

    /**
     * Update time values from RTC
     */
    void update();

    /**
     * Return true every second
     */
    bool isSecond();

    uint8_t getSecond();
    uint8_t getMinute();
    uint8_t getHour();
    uint8_t getDay();
    uint8_t getMonth();
    uint16_t getYear();

private:
    uint32_t targetTime = 0;
    uint8_t second, minute, hour, day, month;
    uint16_t year;
    uint8_t minuteOffset = 14; // minute value from calibrating time
};

#endif