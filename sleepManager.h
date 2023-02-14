#include "config.h"
#include "managerMapper.h"

#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

class SleepManager {
public:
  SleepManager(ManagerMapper* managerMapper);
  void checkSleep();
  void wakeUp();

private:
  ManagerMapper* mapper;
  unsigned int sleepTimer = 0;
};

#endif