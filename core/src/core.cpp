#include "core.h"

Core::Core(bool doInitialization) 
{
	logger = new Logger();
	if (!doInitialization) 
	{
		logger->log("Skipping inicialization");
		return;
	}
	initTTGO();
	initManagers();
}

void Core::initTTGO()
{
	logger->log("Initializating TTGOClass");
    ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL();
}

void Core::initManagers()
{
	//logger->log("Initializating Manager Mapper");
    mapper = new ManagerMapper(ttgo, logger, 10);
	//logger->log("Initializing managers:");
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
	mapper->setManager((uintptr_t) new DisplayManager(mapper));
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }