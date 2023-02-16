#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "colors.h"
#include "managers.h"
#include "core.h"

#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"
#include "displayManager.h"

Core *core;
TTGOClass *ttgo;
ManagerMapper *mapper;

uint8_t hh, mm, ss, mmonth, dday; // H, M, S variables
uint16_t yyear;					  // Year is 16 bit int

byte xcolon = 0; // location of the colon

void displayTime(boolean fullUpdate)
{

	byte xpos = 40; // Stating position for the display
	byte ypos = 90;

	TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
	tmmMng->update();

	ss = tmmMng->getSecond();
	mm = tmmMng->getMinute();
	hh = tmmMng->getHour();
	dday = tmmMng->getDay();
	mmonth = tmmMng->getMonth();
	yyear = tmmMng->getYear();

	ttgo->tft->setTextSize(1);

	if (fullUpdate)
	{
		// Font 7 is a 7-seg display but only contains
		// characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .

		ttgo->tft->setTextColor(0x39C4, TFT_BLACK); // Set desired color
		ttgo->tft->drawString("88:88", xpos, ypos, 7);
		ttgo->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange

		if (hh < 10)
			xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
		xpos += ttgo->tft->drawNumber(hh, xpos, ypos, 7);
		xcolon = xpos + 3;
		xpos += ttgo->tft->drawChar(':', xcolon, ypos, 7);
		if (mm < 10)
			xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
		ttgo->tft->drawNumber(mm, xpos, ypos, 7);
	}

	if (ss % 2)
	{ // Toggle the colon every second
		ttgo->tft->setTextColor(0x39C4, TFT_BLACK);
		xpos += ttgo->tft->drawChar(':', xcolon, ypos, 7);
		ttgo->tft->setTextColor(0xFBE0, TFT_BLACK);
	}
	else
	{
		ttgo->tft->drawChar(':', xcolon, ypos, 7);
	}
	ttgo->tft->setTextSize(3);
	ttgo->tft->setCursor(10, 210);

	ttgo->tft->print(dday);
	ttgo->tft->print("/");
	ttgo->tft->print(mmonth);
	ttgo->tft->print("/");
	ttgo->tft->print(yyear);
}

void setup()
{
	Serial.begin(115200);

	core = new Core();

	ttgo = core->getTTGO();
	mapper = core->getMapper();
	ttgo->openBL();	   // Turn on the backlight
}

void loop()
{
	SleepManager *slpMng = (SleepManager *)mapper->getManager(SLP_MNG);
	TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
	TimeManager *tmmMng = (TimeManager *)mapper->getManager(TMM_MNG);
	DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);

	/*if (tmmMng->isSecond())
	{
		displayTime(ss == 0);
		slpMng->checkSleep();
	}

	int16_t x, y;
	if (tchMng->isTouch(&x, &y))
	{
		while (tchMng->isTouch(&x, &y))
		{
		} // wait for user to release
		displayTime(true);
		slpMng->wakeUp();
	}*/

	dspMng->setBGColor(CYAN_16);
	dspMng->clear();
}
