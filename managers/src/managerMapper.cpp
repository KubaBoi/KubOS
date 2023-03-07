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

SysCall *ManagerMapper::getSysCalls() { return syscalls; }

void ManagerMapper::clearSysCalls()
{
	while (syscalls)
	{
		SysCall *old = syscalls;
		syscalls = (SysCall *)syscalls->remove();
		delete (old);
	}
}

bool ManagerMapper::newSysCall(uintptr_t app, uint8_t syscall, uintptr_t *memory)
{
	if (syscalls)
		syscalls = (SysCall *)syscalls->addAfter(new SysCall(app, syscall, memory));
	else
		syscalls = new SysCall(app, syscall, memory);
	return syscalls;
}