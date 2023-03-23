#include "keyBoardApp.h"

KeyBoardApp::KeyBoardApp() : App("Key Board App")
{
    textArea  = lv_textarea_create(lv_scr_act(), NULL);
    lv_obj_align(textArea, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 16);
    lv_textarea_set_text(textArea, "");
    lv_coord_t max_h = LV_VER_RES / 2 - LV_DPI / 8;
    if(lv_obj_get_height(textArea) > max_h) lv_obj_set_height(textArea, max_h);

    keyboard = lv_keyboard_create(lv_scr_act(), NULL);
    lv_keyboard_set_cursor_manage(keyboard, true);
    lv_obj_set_event_cb(keyboard, keyboardEvent);
    lv_keyboard_set_textarea(keyboard, textArea);
}

void KeyBoardApp::keyboardEvent(lv_obj_t *obj, lv_event_t e)
{
    lv_keyboard_def_event_cb(obj, e);
    if(e == LV_EVENT_CANCEL) {
        lv_keyboard_set_textarea(obj, NULL);
        lv_obj_del(obj);
        obj = NULL;
    }
}