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

	/*lv_obj_t *label;
	lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn1, event_handler);
	lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Button");

	lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn2, event_handler);
	lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
	lv_btn_set_checkable(btn2, true);
	lv_btn_toggle(btn2);
	lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

	label = lv_label_create(btn2, NULL);
	lv_label_set_text(label, "Toggled");*/


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
