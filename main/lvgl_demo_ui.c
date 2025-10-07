/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/examples.html#loader-with-arc

#include "lvgl.h"

static lv_obj_t * btn;
static lv_display_rotation_t rotation = LV_DISP_ROTATION_0;
extern const lv_image_dsc_t Fan;

static void btn_cb(lv_event_t * e)
{
    lv_display_t *disp = lv_event_get_user_data(e);
    rotation++;
    if (rotation > LV_DISP_ROTATION_270) {
        rotation = LV_DISP_ROTATION_0;
    }
    lv_disp_set_rotation(disp, rotation);
}
static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

/* Animation callback to set angle */
void set_img_rotation(void *img, int32_t v)
{
    lv_img_set_angle(img, v * 10); // LVGL uses 0.1° units (so 10 = 1°)
}

void img_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_display_get_screen_active(disp);

    lv_obj_t *fan_img = lv_image_create(scr);
    lv_image_set_src(fan_img, &Fan);

    // Remove padding/borders and adjust scale
    lv_obj_set_style_pad_all(fan_img, 0, 0);
    lv_obj_set_style_border_width(fan_img, 0, 0);
    lv_obj_set_style_radius(fan_img, 0, 0);
    lv_img_set_zoom(fan_img, 192);   // ~75% scale

    lv_obj_center(fan_img);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, fan_img);
    lv_anim_set_exec_cb(&a, set_img_rotation);
    lv_anim_set_time(&a, 1000);                  // 6 sec per rotation
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_values(&a, 0, 3600);
    lv_anim_start(&a);
}

void example_lvgl_demo_ui(lv_display_t *disp)
{
    lv_obj_t *scr = lv_display_get_screen_active(disp);

    /*Create an Arc*/
    lv_obj_t * arc = lv_arc_create(scr);
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_duration(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
}
