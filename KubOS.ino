#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "colors.h"
#include "managers.h"

#include "filesystem.h"
#include "logger.h"
#include "core.h"
/*
#include "clock.h"
#include "batteryViewer.h"
#include "gayMeter.h"*/

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;
Logger *logger;

String getOsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
} 

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();
	logger = mapper->getLogger();

	/*core->startApp(new BatteryViewer(), false);
	core->startApp(new GayMeter(), false);
	core->startApp(new Clock());*/
	core->openDesktop();

	FileSystem *fs = core->getFS();
	WifiManager *wifMng = (WifiManager *)mapper->getManager(WIF_MNG);
	//wifMng->connect("vivo Y33s", "heslo1212");

	logger->log("%s", getOsName());

	/*WiFiClientSecure client;
	HTTPClient https;
	String url = "https://seznam.cz";
	if (https.begin(client, url))
	{
		int httpCode = https.GET();
		if (httpCode > 0)
		{
			if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
			{
				//File f = fs->openFile("https.html", "w");
				WiFiClient stream = https.getStream();
				logger->log("SIZE:%d", https.getSize());
				logger->log("%s", stream);

				/*https.writeToStream(&f);
				logger->log("FileWrite: %d", f.getWriteError());
				logger->log("FileSize: %d", f.size());
				f.close();*/
			/*}
		}
		else
		{
			logger->log("[HTTPS] GET... failed, error: %s", https.errorToString(httpCode).c_str());
		}

		https.end();
	}
	else
	{
		logger->log("[HTTPS] Unable to connect");
	}

	char dest[1000];
	fs->readFile("/https.html", dest);
	logger->log("%s", dest);*/
}

void loop()
{
	core->updateManagers();
	core->updateApps();
	core->drawApps();
}
