#include "irqManager.h"

bool IRQManager::irqAxp = false;
bool IRQManager::irqRtc = false;

IRQManager::IRQManager(ManagerMapper *mappern) : Manager(mappern, "IRQ")
{
    pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(
        AXP202_INT, []
        { irqAxp = true; },
        FALLING);

    pinMode(RTC_INT_PIN, INPUT_PULLUP);
    attachInterrupt(
        RTC_INT_PIN, []
        { irqRtc = true; },
        FALLING);

    mapper->getTTGO()->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ |
                                            AXP202_PEK_LONGPRESS_IRQ |
                                            AXP202_VBUS_REMOVED_IRQ |
                                            AXP202_VBUS_CONNECT_IRQ |
                                            AXP202_CHARGING_IRQ,
                                        true);
    mapper->getTTGO()->power->clearIRQ();
}

void IRQManager::update()
{
    interruptAXP();
    interruptRTC();
}

void IRQManager::attachIRQInterrupt(App *app)
{
    if (irqInterrupts)
        irqInterrupts = irqInterrupts->addAfter(app);
    else
        irqInterrupts = new AppObject(app);
}

uint8_t IRQManager::deattachIRQInterrupt(App *app)
{
    if (!irqInterrupts)
        return 0;
    AppObject *search = irqInterrupts->find(app);
    if (search)
        irqInterrupts = search->remove(false);
    else
        return 0;
    return 1;
}

void IRQManager::attachRTCInterrupt(App *app)
{
    if (rtcInterrupts)
        rtcInterrupts = rtcInterrupts->addAfter(app);
    else
        rtcInterrupts = new AppObject(app);
}

uint8_t IRQManager::deattachRTCInterrupt(App *app)
{
    if (!rtcInterrupts)
        return 0;
    AppObject *search = rtcInterrupts->find(app);
    if (search)
        rtcInterrupts = search->remove(false);
    else
        return 0;
    return 1;
}

void IRQManager::interruptAXP()
{
    if (!irqAxp)
        return;

    irqAxp = false;
    AXP20X_Class *power = mapper->getTTGO()->power;
    power->readIRQ();

    AppObject *start = irqInterrupts;
    if (start)
    {
        do
        {
            start->app->irqInterrupt(power);
            start = (AppObject *)start->next;
        } while (start != irqInterrupts);
    }

    power->clearIRQ();
}

void IRQManager::interruptRTC()
{
    if (!irqRtc)
        return;

    irqRtc = false;
    PCF8563_Class *rtc = mapper->getTTGO()->rtc;

    if (rtcInterrupts)
    {
        AppObject *start = rtcInterrupts;
        do
        {
            start->app->rtcInterrupt(rtc);
            start = (AppObject *)start->next;
        } while (start != rtcInterrupts);
    }
}