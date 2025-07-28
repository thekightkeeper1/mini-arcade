/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/examples.html#loader-with-arc

#include "lvgl.h"

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

lv_obj_t *make_paddle(lv_display_t *disp) {
    /*Create an Rect*/
    lv_obj_t * my_rect = lv_obj_create(lv_scr_act());
    lv_obj_set_size(my_rect , 4, 36);
    lv_obj_set_pos(my_rect , 100, 100);
    lv_obj_set_style_bg_color(my_rect, lv_color_make(0,0,0), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(my_rect, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(my_rect, 0, LV_STATE_DEFAULT);

    return my_rect;
}

lv_obj_t *example_lvgl_demo_ui(lv_display_t *disp)
{

    lv_disp_set_rotation(disp, LV_DISP_ROTATION_90); // Setting rotation                
    lv_obj_t *scr = lv_display_get_screen_active(disp);
    lv_obj_t *paddle = make_paddle(disp);   
    return paddle;
}



