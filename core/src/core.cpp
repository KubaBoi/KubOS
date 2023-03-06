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
	ttgo->lvgl_begin();
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
	if (!app)
		return;

	if (runningApp)
		runningApp = runningApp->addAfter(app);
	else
		runningApp = new AppObject(app);

	app->initApp(mapper);
	if (rewoke)
		app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
}

void Core::closeApp()
{
	if (!runningApp)
		return;
	// maybe need delete (closingApp);
	runningApp = runningApp->remove();
	if (!runningApp)
		startDesktop();
	runningApp->app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
}

void Core::updateApps()
{
	if (!runningApp)
		startDesktop();
	runningApp->app->update();
	updateBackground();
}

void Core::updateBackground()
{
	AppObject *startApp = runningApp;
	do
	{
		runningApp->app->updateBackground();
		runningApp = runningApp->next;
	} while (startApp != runningApp);
}

void Core::drawApps()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	runningApp->app->draw(dspMng);
	lv_task_handler();
}

void Core::nextApp()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	runningApp = runningApp->next;
	runningApp->app->rewoke(dspMng);
}

void Core::startDesktop()
{
	logger->log("Starting desktop");
	startApp(new Desktop(), true);
}