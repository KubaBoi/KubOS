#include <stdint.h>
#include <soc/rtc.h>

#include "config.h"
#include "managerMapper.h"
#include "sleepManager.h"
#include "batteryManager.h"

TTGOClass *ttgo;
ManagerMapper* mapper;

uint32_t targetTime = 0;       // for next 1 second display update
// uint32_t clockUpTime = 0;      // track the time the clock is displayed

uint8_t hh, mm, ss, mmonth, dday; // H, M, S variables
uint16_t yyear; // Year is 16 bit int

#include <time.h>

void setMenuDisplay(int mSel);

byte xcolon = 0; // location of the colon

void displayTime(boolean fullUpdate)
{

    byte xpos = 40; // Stating position for the display
    byte ypos = 90;

    // Get the current data
    RTC_Date tnow = ttgo->rtc->getDateTime();

    hh = tnow.hour;
    mm = tnow.minute;
    ss = tnow.second;
    dday = tnow.day;
    mmonth = tnow.month;
    yyear = tnow.year;

    int offset = 14;
    if (mm < offset) {
      mm = 60 - (offset - mm);
      if (hh == 0) {
        hh = 23;
      }
      else {
        hh--;        
      }      
    }
    else {
      mm -= offset;
    }

    ttgo->tft->setTextSize(1);

    if (fullUpdate) {
        // Font 7 is a 7-seg display but only contains
        // characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .

        ttgo->tft->setTextColor(0x39C4, TFT_BLACK); // Set desired color
        ttgo->tft->drawString("88:88", xpos, ypos, 7);
        ttgo->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange

        if (hh < 10) xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
        xpos += ttgo->tft->drawNumber(hh, xpos, ypos, 7);
        xcolon = xpos + 3;
        xpos += ttgo->tft->drawChar(':', xcolon, ypos, 7);
        if (mm < 10) xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
        ttgo->tft->drawNumber(mm, xpos, ypos, 7);
    }

    if (ss % 2) { // Toggle the colon every second
        ttgo->tft->setTextColor(0x39C4, TFT_BLACK);
        xpos += ttgo->tft->drawChar(':', xcolon, ypos, 7);
        ttgo->tft->setTextColor(0xFBE0, TFT_BLACK);
    } else {
        ttgo->tft->drawChar(':', xcolon, ypos, 7);
    }
    ttgo->tft->setTextSize(3);
    ttgo->tft->setCursor( 10, 210);

    ttgo->tft->print(mmonth);
    ttgo->tft->print("/");
    ttgo->tft->print(dday);
    ttgo->tft->print("/");
    ttgo->tft->print(yyear);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Booting");
    //initSetup();
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->tft->setTextFont(1);
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
    //LVGL is not used, this line is not needed
    // ttgo->lvgl_begin();

    //Check if the RTC clock matches, if not, use compile time
    ttgo->rtc->check();

    //Synchronize time to system time
    ttgo->rtc->syncToSystem();

    displayTime(true); // Our GUI to show the time
    ttgo->openBL(); // Turn on the backlight
  
    Serial.println("Creating managers");
    mapper = new ManagerMapper(ttgo, 10);
    mapper->setManager("SLP", (uintptr_t) new SleepManager(mapper));
    mapper->setManager("BTR", (uintptr_t) new BatteryManager(mapper));
}

void loop()
{
    SleepManager* slpMng = (SleepManager*) mapper->getManager(0);
    
    if (targetTime < millis()) {
        targetTime = millis() + 1000;
        displayTime(ss == 0); // Call every second but only update time every minute

        slpMng->checkSleep();
    }

    int16_t x, y;
    if (ttgo->getTouch(x, y)) {
        while (ttgo->getTouch(x, y)) {} // wait for user to release
        displayTime(true);
        slpMng->wakeUp();
    }
}
