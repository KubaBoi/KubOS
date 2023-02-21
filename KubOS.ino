#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "colors.h"
#include "managers.h"
#include "logger.h"
#include "core.h"

#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"
#include "displayManager.h"

#include "cmd.h"
#include "clock.h"
#include "batteryViewer.h"

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();

	core->startApp(new CMD());
	core->startApp(new BatteryViewer());
	core->startApp(new Clock());
}

void loop()
{
	core->updateManagers();

	SleepManager *slpMng = (SleepManager *)mapper->getManager(SLP_MNG);
	TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
	TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);

	int16_t x, y;
	if (tchMng->isTouch(&x, &y))
	{
		while (tchMng->isTouch(&x, &y))
		{
		};
		// displayTime(true);
		slpMng->wakeUp();
		core->nextApp();
		// core->closeApp();
	}

	core->updateApps();
	core->drawApps();
}
