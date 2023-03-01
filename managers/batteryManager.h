#include "config.h"
#include "managers.h"
#include "manager.h"
#include "irqManager.h"

#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

/**
 * Class for getting informations about power management
 */
class BatteryManager : public Manager
{
public:
	BatteryManager(ManagerMapper *mappern);

	// Return `true` if watches are connected in USB
	bool isCharging();
	// Return battery percentage
	int getPercentage();
	// Return voltage of USB
	float getVbusVoltage();
	// Return current of USB
	float getVbusCurrent();
	// Return voltage of battery
	float getBattVoltage();
};

#endif