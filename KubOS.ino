#include <stdint.h>
#include <soc/rtc.h>
#include <time.h>

#include "config.h"
#include "managers.h"

#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"
#include "timeManager.h"
#include "touchManager.h"

TTGOClass *ttgo;
ManagerMapper *mapper;

uint32_t targetTime = 0; // for next 1 second display update
// uint32_t clockUpTime = 0;      // track the time the clock is displayed

uint8_t hh, mm, ss, mmonth, dday; // H, M, S variables
uint16_t yyear;					  // Year is 16 bit int

void setMenuDisplay(int mSel);

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
	Serial.println("Booting");

	ttgo = TTGOClass::getWatch();
	ttgo->begin();
	ttgo->tft->setTextFont(1);
	ttgo->tft->fillScreen(TFT_BLACK);
	ttgo->tft->setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
	// LVGL is not used, this line is not needed
	//  ttgo->lvgl_begin();

	Serial.println("Creating managers");
	mapper = new ManagerMapper(ttgo, 10);
	mapper->setManager((uintptr_t) new SleepManager(mapper));
	mapper->setManager((uintptr_t) new BatteryManager(mapper));
	mapper->setManager((uintptr_t) new TimeManager(mapper));
	mapper->setManager((uintptr_t) new TouchManager(mapper));

	displayTime(true); // Our GUI to show the time
	ttgo->openBL();	   // Turn on the backlight
}

void loop()
{
	SleepManager *slpMng = (SleepManager *)mapper->getManager(SLP_MNG);
	TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);

	if (targetTime < millis())
	{
		targetTime = millis() + 1000;
		displayTime(ss == 0); // Call every second but only update time every minute

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
	}
}
