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
	mapper->setManager((uintptr_t) new IRQManager(mapper));
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
	mapper->setManager((uintptr_t) new DisplayManager(mapper));
}

void Core::updateManagers()
{
	for (int i = 0; i < mapper->getManagerCount(); i++)
	{
		Manager *mng = (Manager *)mapper->getManager(i);
		mng->update();
	}
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }

void Core::startApp(App *app, bool rewoke)
{
	if (runningApp)
	{
		appObject *newApp = (appObject *)malloc(sizeof(appObject));
		newApp->next = runningApp->next; // next of new app is next of runningApp
		newApp->prev = runningApp;		 // prev of new app is runningApp
		runningApp->next->prev = newApp; // prev of prev of next is new app
		runningApp->next = newApp;		 // next of runningApp is new app
		runningApp = newApp;			 // runningApp is now new app
	}
	else
	{
		runningApp = (appObject *)malloc(sizeof(appObject));
		runningApp->next = runningApp;
		runningApp->prev = runningApp;
	}

	app->initApp(mapper);
	if (rewoke)
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
		runningApp->app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
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

void Core::nextApp()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	if (!runningApp)
		return;
	runningApp = runningApp->next;
	runningApp->app->rewoke(dspMng);
}