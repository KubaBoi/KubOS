#include "managerMapper.h"

#ifndef MANAGER_H
#define MANAGER_H

/**
 * Class for manager inheritance
 */
class Manager
{
public:
	ManagerMapper *mapper;

	Manager(ManagerMapper *mappern);
	void update();
};

#endif