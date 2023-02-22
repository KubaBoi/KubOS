#include "alarmManager.h"

uint16_t AlarmManager::alarmCount = 24 * 60;

AlarmManager::AlarmManager(ManagerMapper *mappern) : Manager(mappern, "ALM")
{
    mapper->getTTGO()->rtc->resetAlarm();
    for (uint16_t i = 0; i < alarmCount; i++)
        alarms[i] = 0;
}

void AlarmManager::update()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    if (irqMng->RTCAlarm)
    {
        setNextAlarm();
        mapper->getTTGO()->motor->onec(1000);
    }
}

void AlarmManager::setAlarm(uint8_t hour, uint8_t minute)
{
    alarms[hour * 60 + minute] = 1;
    setNextAlarm();
    // new RTC_Alarm(minute, hour, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
}

bool AlarmManager::setNextAlarm()
{
    mapper->getTTGO()->rtc->resetAlarm();
    uint8_t hour, minute;
    if (!getNextAlarm(&hour, &minute))
    {
        log("No alarms found");
        mapper->getTTGO()->rtc->disableAlarm();
        return false;
    }

    TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
    if (minute > 60 - tmmMng->getOffset())
    {
        minute = tmmMng->getOffset() - (60 - minute);
        if (hour == 0)
            hour = 23;
        else
            hour--;
    }
    else
        minute += tmmMng->getOffset();

    mapper->getTTGO()->rtc->setAlarm(hour, minute, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
    mapper->getTTGO()->rtc->enableAlarm();
    return true;
}

bool AlarmManager::getNextAlarm(uint8_t *hour, uint8_t *minute)
{
    TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
    uint16_t minuteAct = tmmMng->getMinute();
    uint16_t hourAct = tmmMng->getHour();

    for (uint16_t i = hourAct * 60 + minuteAct + 1; i < this->alarmCount; i++)
        if (alarms[i])
        {
            *hour = i / 60;
            *minute = i - (*hour * 60);
            return true;
        }

    for (uint16_t i = 0; i < hourAct * 60 + minuteAct + 1; i++)
        if (alarms[i])
        {
            *hour = i / 60;
            *minute = i - (*hour * 60);
            return true;
        }
    return false;
}