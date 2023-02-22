#include "sleepManager.h"

SleepManager::SleepManager(ManagerMapper *mappern) : Manager(mappern, "SLP")
{
	pinMode(TOUCH_INT, INPUT);
}

void SleepManager::update()
{
	IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
	if (irqMng->PEKlongPress)
		sleep();

	BatteryManager *btrMng = (BatteryManager *)mapper->getManager(BTR_MNG);
	TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
	int16_t x, y;
	if (btrMng->isCharging() || tchMng->isTouch(&x, &y))
		wakeUp();

	TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
	if (!tmmMng->isSecond())
		return;

	sleepTimer++;
	if (sleepTimer == SHADE_TIME)
		mapper->getTTGO()->setBrightness(50);

	else if (sleepTimer == SCREEN_TIME)
		mapper->getTTGO()->closeBL();

	else if (sleepTimer >= SLEEP_TIME)
	{
		sleepTimer = 0;
		sleep();
	}
}

void SleepManager::wakeUp()
{
	mapper->getTTGO()->setBrightness(100);
	mapper->getTTGO()->openBL();
	sleepTimer = 0;
}

void SleepManager::sleep()
{
	mapper->getTTGO()->displaySleep();
	mapper->getTTGO()->powerOff();

	mapper->getTTGO()->power->setPowerOutPut(AXP202_LDO3, false);
	mapper->getTTGO()->power->setPowerOutPut(AXP202_LDO4, false);
	mapper->getTTGO()->power->setPowerOutPut(AXP202_LDO2, false);
	mapper->getTTGO()->power->setPowerOutPut(AXP202_EXTEN, false);
	mapper->getTTGO()->power->setPowerOutPut(AXP202_DCDC2, false);

	// TOUCH SCREEN  Wakeup source
	esp_sleep_enable_ext1_wakeup(GPIO_SEL_38, ESP_EXT1_WAKEUP_ALL_LOW);
	// ALARM Wakeup
	TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
	AlarmManager *almMng = (AlarmManager *)mapper->getManager(ALM_MNG);
	uint8_t hour, minute, hourAct, minuteAct;
	uint32_t sleepTime = 0;
	if (almMng->getNextAlarm(&hour, &minute))
	{
		hourAct = tmmMng->getHour();
		if (hour <= hourAct)
			sleepTime = (23 - hourAct) + hour;
		else
			sleepTime = hour - hourAct;
		sleepTime *= 60;

		minuteAct = tmmMng->getMinute();
		if (minute <= minuteAct)
			sleepTime += (59 - minuteAct) + minute;
		else
			sleepTime += minute - minuteAct;
		sleepTime *= 60;
		/*std::string s = std::to_string(sleepTime);
		char *pchar = (char *)s.c_str();
		log(pchar);*/

		esp_sleep_enable_timer_wakeup(sleepTime * 1000000ULL);
	}
	// TILT Wakeup source
	// esp_sleep_enable_ext1_wakeup(GPIO_SEL_39, ESP_EXT1_WAKEUP_ANY_HIGH);
	// PEK KEY  Wakeup source
	// esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
	esp_deep_sleep_start();
}