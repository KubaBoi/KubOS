#include "core.h"

Core::Core(bool doInitialization)
{
	logger = new Logger();
	if (!doInitialization)
	{
		logger->log("Skipping inicialization");
		return;
	}
	initTTGO();
	initManagers();
}

void Core::initTTGO()
{
	logger->log("Initializating TTGOClass");
	ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL();
}

void Core::initManagers()
{
	logger->log("Initializating Manager Mapper");
	mapper = new ManagerMapper(ttgo, logger, 10);
	logger->log("Initializing managers:");
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
	mapper->setManager((uintptr_t) new DisplayManager(mapper));
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }

void Core::startApp(App *app)
{
	if (runningApps)
	{
		appObject *newApp = (appObject *)malloc(sizeof(appObject));
		newApp->next = runningApps->next; // next of new app is next of runningApps
		runningApps->next->prev = newApp; // prev of prev of next is new app
		newApp->prev = runningApps;		  // prev of new app is runningApps
		runningApps = newApp;			  // runningApps is now new app
	}
	else
	{
		runningApps = (appObject *)malloc(sizeof(appObject));
		runningApps->next = runningApps;
		runningApps->prev = runningApps;
	}

	app->initApp(mapper);
	runningApps->app = app;
}

void Core::closeApp(App *app)
{
}

void Core::updateApps()
{
	if (!runningApps)
		return;
	appObject *startApp = runningApps;
	do
	{
		runningApps->app->update();
		runningApps = runningApps->next;
	} while (startApp != runningApps);
}

void Core::drawApps()
{
	if (!runningApps)
		return;
	appObject *startApp = runningApps;
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	do
	{
		runningApps->app->draw(dspMng);
		runningApps = runningApps->next;
	} while (startApp != runningApps);
}