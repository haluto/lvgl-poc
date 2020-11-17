/**
 * @file tyin_demo.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"
#include "tyin_demo.h"
#include <stdio.h>
#include <stdlib.h>

#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void focus_cb(lv_group_t * group);
static void list_event_cb(lv_obj_t *list, lv_event_t event);
static void event_handler(lv_obj_t * obj, lv_event_t event);


static void status_bar_create(void);
/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t*  g;
static lv_obj_t * list1;
static lv_obj_t * status_bar;
static lv_obj_t * sb_label;
/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
extern void message_box_create(lv_group_t *g);

void tyin_demo(void)
{
	g = lv_group_create();
	lv_group_set_focus_cb(g, focus_cb);

#if LV_EX_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    lv_indev_t * kb_indev = lv_indev_drv_register(&kb_drv);
    lv_indev_set_group(kb_indev, g);
#endif

	/*Create a list*/
	list1 = lv_list_create(lv_scr_act(), NULL);
	lv_coord_t w = LV_HOR_RES_MAX;
	lv_coord_t h = LV_VER_RES_MAX;
	lv_coord_t statusbar_h = 30;
	lv_obj_set_x(list1, 0);
	lv_obj_set_y(list1, statusbar_h);
	lv_obj_set_size(list1, w, h-statusbar_h);
	//lv_obj_align(list1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_event_cb(list1, list_event_cb);
	lv_group_add_obj(g, list1);
	lv_group_focus_obj(list1);

	/*Add buttons to the list*/
	lv_obj_t * list_btn;

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "New");
	lv_obj_set_event_cb(list_btn, event_handler);
	//lv_list_focus(list_btn, false);
	//lv_list_focus_btn(list1, list_btn);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Open");
	lv_obj_set_event_cb(list_btn, event_handler);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete");
	lv_obj_set_event_cb(list_btn, event_handler);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit");
	lv_obj_set_event_cb(list_btn, event_handler);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save");
	lv_obj_set_event_cb(list_btn, event_handler);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_BELL, "Notify");
	lv_obj_set_event_cb(list_btn, event_handler);

	list_btn = lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "Battery");
	lv_obj_set_event_cb(list_btn, event_handler);


	status_bar_create();
}



/**********************
 *   STATIC FUNCTIONS
 **********************/
static void focus_cb(lv_group_t * group)
{
	printf("focus_cb\n");
	//TODO:
	// if no focused object, set focus on the menu list.
}

static void list_event_cb(lv_obj_t *list, lv_event_t event)
{
	if(event == LV_EVENT_REFRESH) {
		printf("list_event_cb: %d\n", event);
	}
}

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked: %s\n", lv_list_get_btn_text(obj));
        if(1) {
        	message_box_create(g);
        	lv_event_send(status_bar, LV_EVENT_REFRESH, NULL);
        }
    }
}




static int count = 1;
static void status_bar_event_cb(lv_obj_t *list, lv_event_t event)
{
	printf("status_bar_event_cb\n");
	if(event == LV_EVENT_REFRESH) {
		count ++;
		printf("status_bar_event_cb: refreshed %d times\n", count);

		char str[25];
		sprintf(str, "refreshed %d", count);
		lv_label_set_text(sb_label, str);
	}
}

static void status_bar_create(void)
{
	lv_obj_t * cont;
	cont = lv_cont_create(lv_scr_act(), NULL);
	status_bar = cont;
	lv_coord_t w = LV_HOR_RES_MAX;
	lv_coord_t h = LV_VER_RES_MAX;
	lv_coord_t statusbar_h = 30;
	lv_obj_set_x(cont, 0);
	lv_obj_set_y(cont, 0);
	lv_obj_set_size(cont, w, statusbar_h);
	lv_obj_set_event_cb(cont, status_bar_event_cb);

	lv_obj_t * label;
	label = lv_label_create(cont, NULL);
	sb_label = label;
	char str[25];
	sprintf(str, "refreshed %d", count);
	lv_label_set_text(label, str);
}




