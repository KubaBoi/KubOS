#include "managerMapper.h"

ManagerMapper::ManagerMapper(TTGOClass *ttgoClass, Logger *loggern, unsigned int managerCount)
{
	addresses = (uintptr_t *)malloc(sizeof(uintptr_t) * managerCount);
	ttgo = ttgoClass;
	manCount = managerCount;
	logger = loggern;
}

TTGOClass *ManagerMapper::getTTGO() { return ttgo; }

uintptr_t ManagerMapper::getManager(unsigned int index) 
{
	return addresses[index];
}

unsigned int ManagerMapper::getManagerCount() { return manIter; }

void ManagerMapper::setManager(uintptr_t addr)
{
	addresses[manIter++] = addr;
}

Logger *ManagerMapper::getLogger() { return logger; }