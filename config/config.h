#include "syscalls.h"

#define LILYGO_WATCH_2020_V3
#define VERSION "0.0.1"

#define SCREEN_SIZE 240
#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 230

#define CHAR_WIDTH 4
#define CHAR_HEIGHT 8

#define SHADE_TIME 20 // in seconds
#define SCREEN_TIME 30 // in seconds
#define SLEEP_TIME 120 // in seconds

#define LOGGER_SIZE 256 // buffer size
#define LOGGER_LENGTH 40 // line length
#define LOGGER_MAX_LENGTH LOGGER_LENGTH * 4 // max length of one log

#define MIN_DRAG_DIST 5 // minimal drag distance

#define LILYGO_WATCH_LVGL   
#define LILYGO_WATCH_LVGL_FS 

#include <LilyGoWatch.h>