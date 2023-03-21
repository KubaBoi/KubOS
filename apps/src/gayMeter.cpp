#include "gayMeter.h"

GayMeter::GayMeter() : App("Gay Meter")
{
	screen = lv_obj_create(NULL, NULL);

	lv_obj_t *label;
	lv_obj_t *btn1 = lv_btn_create(screen, NULL);
	lv_obj_set_event_cb(btn1, click);
	lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 40);

	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Button");
}

void GayMeter::rewoke()
{
	gayValue = 0;
}

void GayMeter::click(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		Serial.printf("Clicked\n");
		lv_obj_set_x(obj, -20);
	}
}