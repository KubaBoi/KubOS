#include "sleepManager.h"

SleepManager::SleepManager(ManagerMapper *mappern) : Manager(mappern)
{
	logger->log("...Sleep Manager");
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
	// PEK KEY  Wakeup source
	// esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
	esp_deep_sleep_start();
}