#include "managers.h"
#include "manager.h"
#include "irqManager.h"
#include "timeManager.h"

#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

/**
 * Class controlling alarms saved in RTC
 */
class AlarmManager : public Manager
{
public:
    AlarmManager(ManagerMapper *mappern);
    void update();

    // add new alarm into array
    void setAlarm(uint8_t hour, uint8_t minute);

    // return first next alarm
    bool getNextAlarm(uint8_t *hour, uint8_t *minute);

private:
    static uint16_t alarmCount;
    // set next alarm int RTC
    bool setNextAlarm();
    bool alarms[24 * 60];
};

#endif