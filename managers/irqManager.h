#include "config.h"
#include "manager.h"

#ifndef IRQ_MANAGER_H
#define IRQ_MANAGER_H

/**
 * Class reads IRQ interrupts
 */
class IRQManager : public Manager
{
public:
    IRQManager(ManagerMapper *mappern);
    void update();

    bool PEKshortPress,
        PEKlongPress,
        VBUSremoved,
        VBUSconnect,
        RTCAlarm;

    static bool irqAxp;
    static bool irqRtc;

private:
    void interruptAXP();
    void interruptRTC();
};

#endif