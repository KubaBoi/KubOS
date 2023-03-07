#include <stdint.h>
#include "config.h"
#include "logger.h"
#include "sysCall.h"

#ifndef MANAGER_MAPPER_H
#define MANAGER_MAPPER_H

/**
 * Class containing list of addresses of managers and instance of ttgo
 * indexes table is stored in config/managers.h
 */
class ManagerMapper
{
public:
	ManagerMapper(TTGOClass *ttgoClass, Logger *loggern, unsigned int managerCount);
	TTGOClass *getTTGO();

	/**
	 * Return address of manager at given index
	 * address need to be converted into wanted class type of managers
	 */
	uintptr_t getManager(unsigned int index);

	// Return count of stored managers
	unsigned int getManagerCount();

	/**
	 * Creates manager
	 * addr - is address of manager class object
	 */
	void setManager(uintptr_t addr);

	// Return logger
	Logger *getLogger();

	// Return syscalls
	SysCall *getSysCalls();

	// Clears syscalls
	void clearSysCalls();

	// set new sysCall
	bool newSysCall(uintptr_t app, uint8_t syscall, uintptr_t *memory);

private:
	uintptr_t *addresses;	  // list of addresses of managers
	unsigned int manCount;	  // size of addresses
	unsigned int manIter = 0; // count of stored managers
	TTGOClass *ttgo;		  // pointer to watch object
	Logger *logger;			  // logger
	SysCall *syscalls = nullptr;
};

#endif