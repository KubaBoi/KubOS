#include "core.h"

Core::Core()
{
	scroll = 0;
	logger = new Logger();
	logger->log("KubOS %s", VERSION);
	logger->log("0x%x Logger", logger);

	initTTGO();
	initManagers();

	startDesktop();
}

void Core::initTTGO()
{
	ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->openBL();
	logger->log("0x%x TTGOClass", ttgo);
}

void Core::initManagers()
{
	mapper = new ManagerMapper(ttgo, logger, 10);
	logger->log("0x%x ManagerMapper", mapper);
	logger->log("Initializing managers:");
	mapper->setManager((uintptr_t) new IRQManager(mapper));
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));
	mapper->setManager((uintptr_t) new DisplayManager(mapper));
	mapper->setManager((uintptr_t) new AlarmManager(mapper));
}

void Core::updateManagers()
{
	for (int i = 0; i < mapper->getManagerCount(); i++)
	{
		Manager *mng = (Manager *)mapper->getManager(i);
		mng->update();
	}

	IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
	if (irqMng->PEKshortPress)
		nextApp();
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

	if (app)
	{
		app->initApp(mapper);
		if (rewoke)
			app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
	}
	else if (rewoke)
		rewokeDesktop((DisplayManager *)mapper->getManager(DSP_MNG));

	runningApp->app = app;
}

void Core::closeApp()
{
	if (!runningApp)
		return;
	if (!runningApp->app)
		return; // desktop

	appObject *closingApp = runningApp;
	if (closingApp != closingApp->prev)
	{
		closingApp->next->prev = closingApp->prev;
		closingApp->prev->next = closingApp->next;
		runningApp = closingApp->prev;
		if (runningApp->app)
			runningApp->app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
		else
			rewokeDesktop((DisplayManager *)mapper->getManager(DSP_MNG));
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
	if (!runningApp->app)
		updateDesktop();
	else
		runningApp->app->update();
}

void Core::updateBackground()
{
	if (!runningApp)
		return;
	appObject *startApp = runningApp;
	do
	{
		// desktop is not updated in background
		if (runningApp->app)
			runningApp->app->updateBackground();
		runningApp = runningApp->next;
	} while (startApp != runningApp);
}

void Core::drawApps()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	TFT_eSPI *tft = dspMng->getTFT();
	if (!runningApp)
		startDesktop();
	else if (runningApp->app)
		runningApp->app->draw(dspMng);
	else
		drawDesktop(dspMng);
}

void Core::nextApp()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	if (!runningApp)
		return;
	runningApp = runningApp->next;
	if (runningApp->app)
		runningApp->app->rewoke(dspMng);
	else
		rewokeDesktop(dspMng);
}

void Core::startDesktop()
{
	logger->log("Starting desktop");
	startApp(nullptr, true); // appObject with null app
}

void Core::updateDesktop()
{
	TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
	int16_t x, y;
	double dist;
	if (!tchMng->isDrag(&x, &y, &dist))
		return;
	scroll = y / 4;
}

void Core::drawDesktop(DisplayManager *dspMng)
{
	TFT_eSPI *tft = dspMng->getTFT();
	uint8_t ROWS = 29;
	for (int i = ROWS; i > 0; i--)
	{
		uint8_t y = SCREEN_SIZE - i * 8;
		uint8_t length = strlen(logger->getLastLog(i + scroll));
		dspMng->printText(logger->getLastLog(i + scroll), 0, y);
		dspMng->printText(logger->clear, length * 6, y);
	}
}

void Core::rewokeDesktop(DisplayManager *dspMng)
{
	dspMng->resetDefaultFont();
	dspMng->clear();
	scroll = 0;
}