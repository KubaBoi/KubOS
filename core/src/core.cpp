#include "core.h"

Core::Core()
{
	logger = new Logger();
	logger->log("KubOS %s", VERSION);
	logger->log("%#x Logger", logger);

	setupSyscalls();

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
	logger->log("%#x TTGOClass", ttgo);
}

void Core::initManagers()
{
	mapper = new ManagerMapper(ttgo, logger, 10);
	logger->log("%#x ManagerMapper", mapper);
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
	manageSysCalls();
}

void Core::manageSysCalls()
{
	SysCall *syscall = mapper->getSysCalls();
	if (!syscall)
		return;

	SysCall *first = syscall;
	do
	{
		switch (syscall->syscall)
		{
		case SYS_CALL_CLOSE:
			syscallCLOSE(syscall, this);
			break;
		case SYS_CALL_START:
			syscallSTART(syscall, this);
			break;
		case SYS_CALL_NEXT:
			syscallNEXT(syscall, this);
			break;
		case SYS_CALL_APPS:
			syscallAPPS(syscall, this);
			break;
		case SYS_CALL_REWOKE:
			syscallREWOKE(syscall, this);
			break;
		default:
			logger->log("SYS_CALL %#06x missing", syscall->syscall);
		}
		syscall = (SysCall *)syscall->next;
	} while (first != syscall);
	mapper->clearSysCalls();
}

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }

AppObject *Core::getRunningApp() { return runningApp; }

AppObject *Core::setRunningApp(App *app)
{
	AppObject *search = runningApp->find(app);
	if (search)
		runningApp = search;
	return search;
}

void Core::startApp(App *app, bool rewoke)
{
	if (!app)
		return;

	if (runningApp)
		runningApp = runningApp->addAfter(app);
	else
		runningApp = new AppObject(app);

	runningApp->app->initApp(mapper);
	runningApp->app->start();
	if (rewoke)
		runningApp->app->rewoke((DisplayManager *)mapper->getManager(DSP_MNG));
}

App *Core::rewokeApp(App *app)
{
	AppObject *ao = runningApp->find(app);
	if (!ao)
		return nullptr;
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	runningApp->app->sleep();
	runningApp = ao;
	runningApp->app->rewoke(dspMng);
	return runningApp->app;
}

void Core::closeApp()
{
	if (!runningApp)
		return;

	AppObject *old = runningApp;
	runningApp = runningApp->remove();
	delete (old);
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
		runningApp = (AppObject *)runningApp->next;
	} while (startApp != runningApp);
}

void Core::drawApps()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	if (runningApp->app->draw(dspMng))
		lv_task_handler();
}

void Core::nextApp()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	runningApp->app->sleep();
	runningApp = (AppObject *)runningApp->next;
	runningApp->app->rewoke(dspMng);
}

void Core::prevApp()
{
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
	runningApp->app->sleep();
	runningApp = (AppObject *)runningApp->prev;
	runningApp->app->rewoke(dspMng);
}

void Core::startDesktop()
{
	logger->log("Starting desktop");
	startApp(new Desktop(), true);
}

// SYS CALLS

void Core::setupSyscalls()
{
	syscalls[SYS_CALL_CLOSE] = (uintptr_t)syscallCLOSE;
	syscalls[SYS_CALL_START] = (uintptr_t)syscallSTART;
	syscalls[SYS_CALL_NEXT] = (uintptr_t)syscallNEXT;
	syscalls[SYS_CALL_APPS] = (uintptr_t)syscallAPPS;
}

void Core::syscallCLOSE(SysCall *syscall, Core *core)
{
	App *app = (App *)*syscall->memory;
	if (core->setRunningApp(app))
		core->closeApp();
	*syscall->memory = (uintptr_t)core->getRunningApp()->app;
}

void Core::syscallSTART(SysCall *syscall, Core *core)
{
	App *app = (App *)*syscall->memory;
	core->startApp(app);
	*syscall->memory = (uintptr_t)core->getRunningApp()->app;
}

void Core::syscallNEXT(SysCall *syscall, Core *core)
{
	if (syscall->memory)
		core->prevApp();
	else
		core->nextApp();
	*syscall->memory = (uintptr_t)core->getRunningApp()->app;
}

void Core::syscallAPPS(SysCall *syscall, Core *core)
{
	*syscall->memory = (uintptr_t)core->getRunningApp()->app;
}

void Core::syscallREWOKE(SysCall *syscall, Core *core)
{
	*syscall->memory = (uintptr_t)core->rewokeApp((App *)syscall->app);
}
