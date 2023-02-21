#include "config.h"
#include "managers.h"
#include "managerMapper.h"
#include "manager.h"
#include "irqManager.h"
#include "batteryManager.h"
#include "timeManager.h"

#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

/**
 * Class controls sleep of watches for battery saving
 * border constants are stored in config.h
 */
class SleepManager : public Manager
{
public:
	SleepManager(ManagerMapper *managern);

	// Adds one to sleepTimer and decides about saving
	void update();

	// Reset sleepTimer
	void wakeUp();

	/**
	 * puts watches to deep sleep mode
	 * and wakes them up at touch
	 */
	void sleep();

private:
	unsigned int sleepTimer = 0;
};

#endif