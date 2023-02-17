#include "core.h"

Core::Core(bool doInitialization)
{
	logger = new Logger();
	logger->log("KubOS");
	logger->log(VERSION);
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
	if (runningApp)
	{
		appObject *newApp = (appObject *)malloc(sizeof(appObject));
		newApp->next = runningApp->next; // next of new app is next of runningApp
		runningApp->next->prev = newApp; // prev of prev of next is new app
		newApp->prev = runningApp;		 // prev of new app is runningApp
		runningApp = newApp;			 // runningApp is now new app
	}
	else
	{
		runningApp = (appObject *)malloc(sizeof(appObject));
		runningApp->next = runningApp;
		runningApp->prev = runningApp;
	}

	app->initApp(mapper);
	app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
	runningApp->app = app;
}

void Core::closeApp()
{
	if (!runningApp)
		return;
	appObject *closingApp = runningApp;
	if (closingApp != closingApp->prev)
	{
		closingApp->next->prev = closingApp->prev;
		closingApp->prev->next = closingApp->next;
		runningApp = closingApp->prev;
	}
	else
		runningApp = nullptr;
	delete (closingApp->app);
	delete (closingApp);
}

void Core::updateApps()
{
	if (!runningApp)
		return;
	runningApp->app->update();
}

void Core::updateBackground()
{
	if (!runningApp)
		return;
	appObject *startApp = runningApp;
	do
	{
		runningApp->app->updateBackground();
		runningApp = runningApp->next;
	} while (startApp != runningApp);
}

void Core::drawApps()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	if (!runningApp)
	{
		dspMng->getDefaultFont();
		dspMng->clear();
		dspMng->printText("No running application :(", 0, 10);
		return;
	}
	runningApp->app->draw(dspMng);
}