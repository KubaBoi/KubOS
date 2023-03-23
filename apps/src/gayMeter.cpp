#include "gayMeter.h"

char GayMeter::comments[10][100] = {
	"Majitel vaginy",
	"Gay",
	"Hodne gay",
	"Vlazny buh",
	"Multi Chad Penis enjoyer",
	"Clovek co saha na svuj penis a necucha si potom k rukam",
	"Prezident teploty",
	"Super mega gay",
	"Tom the Blondman",
	"Maximalne hyper ultra gay"
};

GayMeter::GayMeter() : App("Gay Meter")
{
	lv_obj_t *label;
	lv_obj_t *btn1 = lv_btn_create(screen, NULL);
	lv_obj_set_event_cb(btn1, click);
	lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 40);

	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Jak moc???");

	gayLabel = lv_label_create(screen, NULL);
	lv_label_set_text(gayLabel, "");
	lv_obj_align(gayLabel, NULL, LV_ALIGN_CENTER, 0, -40);

	gayCommLabel = lv_label_create(screen, NULL);
	lv_label_set_text(gayCommLabel, "");
	lv_label_set_long_mode(gayCommLabel, LV_LABEL_LONG_SROLL_CIRC);
	lv_obj_set_width(gayCommLabel, 150);
	lv_obj_align(gayCommLabel, NULL, LV_ALIGN_CENTER, 0, -70);

	lv_obj_set_user_data(btn1, SELF_APP_ADDR);
	lv_obj_set_user_data(gayLabel, SELF_APP_ADDR);

	choosing = 0;
}

void GayMeter::update()
{
	if (!choosing)
		return;
	choosing--;

	int prc = rand() % 100;
	lv_label_set_text_fmt(gayLabel, "%u %% gay", prc);
	if (!choosing)
		lv_label_set_text(gayCommLabel, comments[prc / 10]);
	else
		lv_label_set_text(gayCommLabel, "");
	lv_obj_align(gayLabel, NULL, LV_ALIGN_CENTER, 0, -40);
}

void GayMeter::click(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		GayMeter *self = (GayMeter *)SELF_APP;
		self->choosing = millis() % 1000;
	}
}