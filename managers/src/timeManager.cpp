#include "timeManager.h"

TimeManager::TimeManager(ManagerMapper *managern) : Manager(managern, "TMM")
{
    managern->getTTGO()->rtc->check();
    managern->getTTGO()->rtc->syncToSystem();
}

void TimeManager::update()
{
    RTC_Date tnow = mapper->getTTGO()->rtc->getDateTime();
    second = tnow.second;
    minute = tnow.minute;
    hour = tnow.hour;
    day = tnow.day;
    month = tnow.month;
    year = tnow.year;

    if (minute < minuteOffset)
    {
        minute = 60 - (minuteOffset - minute);
        if (hour == 0)
            hour = 23;
        else
            hour--;
    }
    else
        minute -= minuteOffset;

    if (targetTime < millis())
    {
        targetTime = millis() + 1000;
        isSec = true;
    }
    else
        isSec = false;
}

bool TimeManager::isSecond() { return isSec; }

uint8_t TimeManager::getSecond() { return second; }
uint8_t TimeManager::getMinute() { return minute; }
uint8_t TimeManager::getHour() { return hour; }
uint8_t TimeManager::getDay() { return day; }
uint8_t TimeManager::getMonth() { return month; }
uint16_t TimeManager::getYear() { return year; }

uint8_t TimeManager::getOffset() { return minuteOffset; }