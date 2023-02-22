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
#include "alarmManager.h"

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

	core->startApp(new CMD(), false);
	core->startApp(new BatteryViewer(), false);
	core->startApp(new Clock());

	AlarmManager *almMng = (AlarmManager *)mapper->getManager(ALM_MNG);
	almMng->setAlarm(8, 0);
	almMng->setAlarm(10, 0);
	almMng->setAlarm(10, 30);
	ttgo->motor_begin();
}

void loop()
{
	core->updateManagers();
	core->updateApps();
	core->drawApps();
}
