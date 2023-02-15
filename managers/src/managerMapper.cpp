#include "managerMapper.h"

ManagerMapper::ManagerMapper(TTGOClass *ttgoClass, unsigned int managerCount)
{
	addresses = (uintptr_t *)malloc(sizeof(uintptr_t) * managerCount);
	ttgo = ttgoClass;
	manCount = managerCount;
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