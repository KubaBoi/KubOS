#include "irqManager.h"

bool IRQManager::irq = false;

IRQManager::IRQManager(ManagerMapper *mappern) : Manager(mappern)
{
    logger->log("...IRQManager");
    pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(
        AXP202_INT, []
        { irq = true; },
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
    if (irq)
    {
        irq = false;
        mapper->getTTGO()->power->readIRQ();

        PEKshortPress = mapper->getTTGO()->power->isPEKShortPressIRQ();
        PEKlongPress = mapper->getTTGO()->power->isPEKLongtPressIRQ();
        VBUSremoved = mapper->getTTGO()->power->isVbusRemoveIRQ();
        VBUSconnect = mapper->getTTGO()->power->isVbusPlugInIRQ();

        mapper->getTTGO()->power->clearIRQ();
    }
    else
    {
        PEKshortPress = false;
        PEKlongPress = false;
        VBUSremoved = false;
        VBUSconnect = false;
    }
}