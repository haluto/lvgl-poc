#include "../../lv_examples.h"
#include <stdio.h>

#if 0
lv_obj_t * ta1;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	//printf("message->event_handler(): %d\n", event);
    if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Value: %s\n", lv_textarea_get_text(obj));
    }
    else if(event == LV_EVENT_LONG_PRESSED_REPEAT) {
        /*For simple test: Long press the Text are to add the text below*/
        const char  * txt = "\n\nYou can scroll it if the text is long enough.\n";
        static uint16_t i = 0;
        if(txt[i] != '\0') {
            lv_textarea_add_char(ta1, txt[i]);
            i++;
        }
    }
    else if(event == LV_EVENT_SHORT_CLICKED) {
    	printf("tyin: message->event_handler()\n");

    	lv_obj_del(obj);
    }
}

void message_box_create(lv_group_t *g)
{
    ta1 = lv_textarea_create(lv_scr_act(), NULL);
    lv_coord_t w = LV_HOR_RES_MAX;
	lv_coord_t h = LV_VER_RES_MAX;
	lv_coord_t statusbar_h = 30;
	lv_obj_set_x(ta1, 0);
	lv_obj_set_y(ta1, statusbar_h);
	lv_obj_set_size(ta1, w, h-statusbar_h);
    lv_textarea_set_text(ta1, "This is a message from ATT");    /*Set an initial text*/
    lv_obj_set_event_cb(ta1, event_handler);

    if(g) {
    	lv_group_add_obj(g, ta1);
    	lv_group_focus_obj(ta1);
    }
}
#else

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	//printf("message->event_handler(): %d\n", event);
    if(event == LV_EVENT_SHORT_CLICKED) {
    	printf("tyin: message->event_handler()\n");

    	lv_obj_del(obj);
    }
}

void message_box_create(lv_group_t *g)
{
	/*Create a page*/
    lv_obj_t * page = lv_page_create(lv_scr_act(), NULL);
    lv_coord_t w = LV_HOR_RES_MAX;
	lv_coord_t h = LV_VER_RES_MAX;
	lv_coord_t statusbar_h = 30;
	lv_obj_set_x(page, 0);
	lv_obj_set_y(page, statusbar_h);
	lv_obj_set_size(page, w, h-statusbar_h);
	lv_obj_set_event_cb(page, event_handler);
	if(g) {
		lv_group_add_obj(g, page);
		lv_group_focus_obj(page);
	}

    /*Create a label on the page*/
    lv_obj_t * label = lv_label_create(page, NULL);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);            /*Automatically break long lines*/
    lv_obj_set_width(label, lv_page_get_width_fit(page));          /*Set the label width to max value to not show hor. scroll bars*/
    lv_label_set_text(label, "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\n"
                             "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
                             "Ut enim ad minim veniam, quis nostrud exercitation ullamco\n"
                             "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure\n"
                             "dolor in reprehenderit in voluptate velit esse cillum dolore\n"
                             "eu fugiat nulla pariatur.\n"
                             "Excepteur sint occaecat cupidatat non proident, sunt in culpa\n"
                             "qui officia deserunt mollit anim id est laborum.");
}
#endif

