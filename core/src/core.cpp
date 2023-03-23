#include "core.h"

Core::Core()
{
	fs = new FileSystem();

	logger = new Logger(fs);
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
		case SYS_CALL_KILL:
			syscallKILL(syscall, this);
			break;
		default:
			logger->log("SYS_CALL %#06x missing", syscall->syscall);
		}
		syscall = (SysCall *)syscall->next;
	} while (first != syscall);
	mapper->clearSysCalls();
}

FileSystem *Core::getFS() { return fs; }

TTGOClass *Core::getTTGO() { return ttgo; }

ManagerMapper *Core::getMapper() { return mapper; }

AppObject *Core::getRunningApp() { return runningApp; }

AppObject *Core::setRunningApp(App *app)
{
	AppObject *search = runningApp->find(app);
	if (search)
	{
		runningApp = search;
		rewokeApp(runningApp);
	}
	return search;
}

void Core::openDesktop()
{
	AppObject *rn = setRunningApp((App *)desktop);
	if (!rn)
		startDesktop();
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
		rewokeApp(runningApp);
}

App *Core::rewokeApp(App *app)
{
	AppObject *ao = runningApp->find(app);
	return rewokeApp(ao);
}

App *Core::rewokeApp(AppObject *ao)
{
	if (!ao)
		return nullptr;
	if (!ao->app)
		return nullptr;

	if (desktop)
		desktop->rewokeOnBc(ao->app);
	else
		logger->log("W: Desktop was not found");

	runningApp->app->sleep();
	runningApp = ao;
	runningApp->app->rewoke();
	if (runningApp->app->screen)
		lv_scr_load(runningApp->app->screen);

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
	rewokeApp(runningApp);
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
	if (runningApp->app->screen)
		lv_task_handler();
	else
	{
		DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
		if (!runningApp->app->draw(dspMng))
		{
			desktop->update();
			desktop->draw(dspMng);
		}
	}
}

void Core::nextApp() { rewokeApp((AppObject *)runningApp->next); }

void Core::prevApp() { rewokeApp((AppObject *)runningApp->prev); }

void Core::startDesktop()
{
	desktop = new Desktop();
	startApp(desktop);
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

void Core::syscallKILL(SysCall *syscall, Core *core)
{
	App *app = (App *)syscall->app;
	core->logger->err("Killed: %s 0x%x", app->name, syscall->app);
	core->logger->err("Because: %s", (char *)syscall->memory);

	AppObject *rnApp = core->runningApp;
	core->runningApp = core->runningApp->find(app);
	bool isSame = (rnApp == core->runningApp);
	core->closeApp();
	if (isSame)
		return;
	core->runningApp = rnApp;
}