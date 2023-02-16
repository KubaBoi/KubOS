#include <iostream>

#include "managerMapper.h"
#include "logger.h"

#ifndef MANAGER_H
#define MANAGER_H

/**
 * Class for manager inheritance
 */
class Manager
{
public:
	ManagerMapper *mapper;
	Logger *logger;

	Manager(ManagerMapper *mappern);
	void update();
};

#endif