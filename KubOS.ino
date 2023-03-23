#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "colors.h"
#include "managers.h"

#include "filesystem.h"
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
#include "gayMeter.h"

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();

	core->startApp(new BatteryViewer(), false);
	core->startApp(new GayMeter(), false);
	core->startApp(new Clock());
	//core->openDesktop();

	FileSystem *fs = core->getFS();
	fs->listAllFiles();
	fs->writeFile("/ahoj.txt", "gagagag");
	fs->writeFile("/ahoj2.txt", "gaergerggagag");
	fs->writeFile("/ahoj3.txt", "gagaga5544g");
	fs->writeFile("/aho4.txt", "gfgagagag");
	
	char targ[LOGGER_MAX_LENGTH];
	if (fs->readFile("/ahoj.txt", targ))
		core->getMapper()->getLogger()->log("%s", targ);
	core->getMapper()->getLogger()->log("%s", fs->listAllFiles());
}

void loop()
{
	core->updateManagers();
	core->updateApps();
	core->drawApps();
}

