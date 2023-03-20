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

#include "clock.h"
#include "batteryViewer.h"
#include "window.h"
#include "gayMeter.h"

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		Serial.printf("Clicked\n");
	}
	else if (event == LV_EVENT_VALUE_CHANGED)
	{
		Serial.printf("Toggled\n");
	}
}

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();

	core->startApp(new BatteryViewer(), false);
	core->startApp(new Clock());
	core->startApp(new GayMeter());

	// core->startApp(new Window());
	// core->startApp(new BatteryViewer(), false);
	// core->startApp(new Clock());

	/*AlarmManager *almMng = (AlarmManager *)mapper->getManager(ALM_MNG);
	almMng->setAlarm(8, 0);
	almMng->setAlarm(10, 0);
	almMng->setAlarm(10, 30);
	ttgo->motor_begin();*/
}

void loop()
{
	core->updateManagers();
	core->updateApps();
	core->drawApps();
}
