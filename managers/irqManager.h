#include "config.h"
#include "manager.h"
#include "appObject.h"

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

    void attachIRQInterrupt(App *app);
    uint8_t deattachIRQInterrupt(App *app);

    void attachRTCInterrupt(App *app);
    uint8_t deattachRTCInterrupt(App *app);

    bool PEKshortPress,
        PEKlongPress,
        VBUSremoved,
        VBUSconnect,
        RTCAlarm = false;

    static bool irqAxp;
    static bool irqRtc;

private:
    AppObject *irqInterrupts;
    AppObject *rtcInterrupts;

    void interruptAXP();
    void interruptRTC();
};

#endif