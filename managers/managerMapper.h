#include <stdint.h>
#include "config.h"

#ifndef MANAGER_MAPPER_H
#define MANAGER_MAPPER_H

/**
Class containing list of addresses of managers and instance of ttgo
0 -> SleepManager
1 -> BatteryManager
2 -> TimeManager
*/
class ManagerMapper
{
public:
	ManagerMapper(TTGOClass *ttgoClass, unsigned int managerCount);
	TTGOClass *getTTGO();

	uintptr_t getManager(unsigned int index);
	unsigned int getManagerCount();
	void setManager(uintptr_t addr);

private:
	uintptr_t *addresses;
	unsigned int manCount;
	unsigned int manIter = 0;
	TTGOClass *ttgo;
};

#endif