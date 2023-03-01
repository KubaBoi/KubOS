#include "batteryManager.h"

BatteryManager::BatteryManager(ManagerMapper *mappern) : Manager(mappern, "BTR") 
{
	mapper->getTTGO()->power->adc1Enable(AXP202_VBUS_VOL_ADC1 |
											 AXP202_VBUS_CUR_ADC1 |
											 AXP202_BATT_CUR_ADC1 |
											 AXP202_BATT_VOL_ADC1,
										 true);
}

bool BatteryManager::isCharging()
{
	return !((getVbusVoltage() < 1) && (getVbusCurrent() < 1));
}

int BatteryManager::getPercentage()
{
	return mapper->getTTGO()->power->getBattPercentage();
}

float BatteryManager::getVbusVoltage()
{
	return mapper->getTTGO()->power->getVbusVoltage();
}

float BatteryManager::getVbusCurrent()
{
	return mapper->getTTGO()->power->getVbusCurrent();
}

float BatteryManager::getBattVoltage()
{
	return mapper->getTTGO()->power->getBattVoltage();
}