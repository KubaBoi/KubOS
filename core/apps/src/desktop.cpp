#include "desktop.h"

Desktop::Desktop() : App("Desktop", false) 
{
    appName = (char *)malloc(LOGGER_LENGTH);
    appName[0] = 0;

    headerFont = (fnt*)malloc(sizeof(fnt));
    headerFont->bgColor = WHITE_16;
    headerFont->color = BLACK_16;
    headerFont->font = 1;
    headerFont->size = 1;
}

Desktop::~Desktop()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->deattachIRQInterrupt(this);
    delete appName;
}

void Desktop::start()
{
    IRQManager *irqMng = (IRQManager *)mapper->getManager(IRQ_MNG);
    irqMng->attachIRQInterrupt(this);
}

void Desktop::rewoke()
{
    DisplayManager *dspMng = (DisplayManager *)mapper->getManager(DSP_MNG);
    dspMng->resetDefaultFont();
	dspMng->clear();
	scroll = 0;
}

void Desktop::rewokeOnBc(App *app)
{
    appName = strncpy(appName, app->name, LOGGER_LENGTH);
    uint16_t length = strlen(appName);
    memset(appName + length, ' ', LOGGER_LENGTH - length);
    appName[LOGGER_LENGTH - 1] = 0;
}

void Desktop::update()
{
    TouchManager *tchMng = (TouchManager *)mapper->getManager(TCH_MNG);
    int16_t x, y;
    double dist;
    if (!tchMng->isDrag(&x, &y, &dist))
        return;
    if (y)
        scroll += (y / abs(y)) * (10 / abs(y) + 1);
}

bool Desktop::draw(DisplayManager *dspMng)
{
    TFT_eSPI *tft = dspMng->getTFT();
    tft->drawRect(WINDOW_WIDTH - 2, CHAR_HEIGHT, 2, WINDOW_HEIGHT, dspMng->getDefaultFont()->bgColor);
    tft->drawRect(WINDOW_WIDTH - 2, WINDOW_HEIGHT - scroll - 1, 2, 4, dspMng->getDefaultFont()->color);
    dspMng->printText("=> %s", 0, 0, headerFont, appName);
    for (int i = 29; i > 0; i--)
        dspMng->printText(logger->getLastLog(i + scroll), 0, SCREEN_SIZE - i * CHAR_HEIGHT);
    return true;
}

void Desktop::irqInterrupt(AXP20X_Class *power)
{
    if (power->isPEKShortPressIRQ())
    {
        *syscallmem = 0;
        mapper->newSysCall((uintptr_t)this, SYS_CALL_NEXT, syscallmem);
    }   
}