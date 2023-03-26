#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "colors.h"
#include "managers.h"

#include "filesystem.h"
#include "logger.h"
#include "core.h"

#include "clock.h"
#include "batteryViewer.h"
#include "gayMeter.h"

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;
Logger *logger;

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();
	logger = mapper->getLogger();

	core->startApp(new BatteryViewer(), false);
	core->startApp(new GayMeter(), false);
	core->startApp(new Clock());
	core->openDesktop();

	WifiManager *wfiMng = (WifiManager *)mapper->getManager(WIF_MNG);
	wfiMng->connect("vivo Y33s", "heslo1212");
}

void loop()
{
	core->updateManagers();
	core->updateApps();
	core->drawApps();
}

