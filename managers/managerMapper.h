#include <stdint.h>
#include "config.h"

#ifndef MANAGER_MAPPER_H
#define MANAGER_MAPPER_H

/**
 * Class containing list of addresses of managers and instance of ttgo
 * indexes table is stored in config/managers.h
 */
class ManagerMapper
{
public:
	ManagerMapper(TTGOClass *ttgoClass, unsigned int managerCount);
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

private:
	uintptr_t *addresses;	  // list of addresses of managers
	unsigned int manCount;	  // size of addresses
	unsigned int manIter = 0; // count of stored managers
	TTGOClass *ttgo;		  // pointer to watch object
};

#endif