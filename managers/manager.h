#include <iostream>
#include <string>

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
	char *name;

	Manager(ManagerMapper *mappern, char *namen);
	void log(char *text);
	virtual void update();
};

#endif