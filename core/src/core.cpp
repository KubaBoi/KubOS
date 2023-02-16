#include "core.h"

Core::Core(bool doInitialization) 
{
	if (!doInitialization) return;
	initTTGO();
	initManagers();
}

void Core::initTTGO()
{
    ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL();
}

void Core::initManagers()
{
    mapper = new ManagerMapper(ttgo, 10);
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
	mapper->setManager((uintptr_t) new DisplayManager(mapper));
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }