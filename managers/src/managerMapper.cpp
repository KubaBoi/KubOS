#include "managerMapper.h"

ManagerMapper::ManagerMapper(TTGOClass *ttgoClass, unsigned int managerCount)
{
	addresses = (uintptr_t *)malloc(sizeof(uintptr_t) * managerCount);
	ttgo = ttgoClass;
	manCount = managerCount;
}

TTGOClass *ManagerMapper::getTTGO() { return ttgo; }

uintptr_t ManagerMapper::getCodeManager(char *name)
{
	int index = -1;
	for (int i = 0; i < manIter; i++)
	{
		Serial.printf("%s\n", name);
	}
	return 0;
}

uintptr_t ManagerMapper::getManager(unsigned int index)
{
	return addresses[index];
}

void ManagerMapper::setManager(char *name, uintptr_t addr)
{
	names[manIter] = (uintptr_t)name;
	addresses[manIter++] = addr;
}