#include "config.h"
#include "managerMapper.h"
#include "manager.h"
#include "batteryManager.h"

#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

/**
Class controls sleep of watches for battery saving
border constants are stored in config.h
*/
class SleepManager : public Manager
{
public:
	SleepManager(ManagerMapper *managerMapper);
	void checkSleep();
	void wakeUp();

private:
	unsigned int sleepTimer = 0;
};

#endif