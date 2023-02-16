#include "core.h"

Core::Core() {}

void Core::initTTGO()
{
    ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->tft->setTextFont(1);
	ttgo->tft->fillScreen(TFT_BLACK);
	ttgo->tft->setTextColor(TFT_YELLOW, TFT_BLACK);
}

void Core::initManagers()
{
    mapper = new ManagerMapper(ttgo, 10);
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }