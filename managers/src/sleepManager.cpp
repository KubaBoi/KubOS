#include "sleepManager.h"

SleepManager::SleepManager(ManagerMapper *mappern) : Manager(mappern) {}

/**
Adds one to sleepTimer and decides about saving
*/
void SleepManager::checkSleep()
{
	BatteryManager *btrMng = (BatteryManager *)mapper->getManager(BTR_MNG);
	if (btrMng->isCharging())
	{
		wakeUp();
	}

	sleepTimer++;
	if (sleepTimer == 1)
	{
		mapper->getTTGO()->setBrightness(100);
		mapper->getTTGO()->openBL();
	}
	else if (sleepTimer == SHADE_TIME)
	{
		mapper->getTTGO()->setBrightness(50);
	}
	else if (sleepTimer == SCREEN_TIME)
	{
		mapper->getTTGO()->closeBL();
	}
	else if (sleepTimer >= SLEEP_TIME)
	{
		sleepTimer = 0;
		mapper->getTTGO()->shutdown();
	}
}

/**
Resets sleepTimer
*/
void SleepManager::wakeUp()
{
	sleepTimer = 0;
}