#include "sleepManager.h"

SleepManager::SleepManager(ManagerMapper* managerMapper) {
  mapper = managerMapper;
}

void SleepManager::checkSleep() {
  sleepTimer++;
  if (sleepTimer == 1) {
    mapper->getTTGO()->setBrightness(100);
    mapper->getTTGO()->openBL();
  }
  else if (sleepTimer == SHADE_TIME) {
    mapper->getTTGO()->setBrightness(50);
  }
  else if (sleepTimer == SCREEN_TIME) {
    mapper->getTTGO()->closeBL();
  }
  else if (sleepTimer >= SLEEP_TIME) {
    sleepTimer = 0;
    mapper->getTTGO()->shutdown();
  }
}

void SleepManager::wakeUp() {
  sleepTimer = 0;
}