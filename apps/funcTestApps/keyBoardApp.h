#include <stdlib.h>

#include "app.h"
#include "touchManager.h"

#ifndef KEY_BOARD_APP_H
#define KEY_BOARD_APP_H

class KeyBoardApp : public App
{
public:
    lv_obj_t *textArea, *keyboard;

    KeyBoardApp();

private:
    static void keyboardEvent(lv_obj_t *obj, lv_event_t e);
};

#endif