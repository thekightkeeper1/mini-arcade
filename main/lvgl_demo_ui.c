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


void example_lvgl_demo_ui(lv_display_t *disp)
{

    lv_disp_set_rotation(disp, LV_DISP_ROTATION_90); // Setting rotation                
    lv_obj_t *scr = lv_display_get_screen_active(disp);



    /*Create an Rect*/
    lv_obj_t * my_rect = lv_obj_create(lv_scr_act());
    lv_obj_set_size(my_rect , 4, 36);
    lv_obj_set_pos(my_rect , 100, 100);
    lv_obj_set_style_bg_color(my_rect, lv_color_make(0,0,0), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(my_rect, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(my_rect, 0, LV_STATE_DEFAULT);


    // lv_obj_t * my_rect2 = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(my_rect2 , 100, 100);
    // lv_obj_set_pos(my_rect2 , 0, 0);
    // lv_obj_set_style_bg_color(my_rect2, lv_color_make(0,0,0), 0);
    

    // // Create an arc
    // lv_obj_t * arc = lv_arc_create(scr);
    // lv_arc_set_rotation(arc, 270);
    // lv_arc_set_bg_angles(arc, 0, 360);
    // lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    // lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    // lv_obj_center(arc);

    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_var(&a, arc);
    // lv_anim_set_exec_cb(&a, set_angle);
    // lv_anim_set_duration(&a, 1000);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    // lv_anim_set_repeat_delay(&a, 500);
    // lv_anim_set_values(&a, 0, 100);
    // lv_anim_start(&a);
}
