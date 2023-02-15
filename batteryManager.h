#include "config.h"
#include "manager.h"

#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

class BatteryManager : public Manager {
public:
  BatteryManager(ManagerMapper* mappern);
  
  bool isCharging();
  int getPercentage();
  float getVbusVoltage();
  float getVbusCurrent();
  float getBattVoltage();
};

#endif