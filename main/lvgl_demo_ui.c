#include "lvgl.h"
#include <stdio.h>

#define PADDLE_WIDTH 6
#define PADDLE_HEIGHT 60
#define PADDLE_MARGIN 10
#define BALL_SIZE 10
#define BORDER_WIDTH 4
#define SCORE_FONT LV_FONT_DEFAULT

typedef enum {
    PLAYER_LEFT,
    PLAYER_RIGHT
} player_t;

static lv_obj_t * scr;
static lv_obj_t * ball;
static lv_obj_t * border;
static lv_obj_t * separator_line;
static lv_obj_t * score_left_label;
static lv_obj_t * score_right_label;

static lv_obj_t * paddle_left = NULL;
static lv_obj_t * paddle_right = NULL;

static int score_left = 0;
static int score_right = 0;

static void paddle(int32_t y_pos, player_t player)
{
    lv_coord_t x_pos;

    // Clamp y_pos
    if (y_pos < 0) y_pos = 0;
    if (y_pos > lv_obj_get_height(scr) - PADDLE_HEIGHT)
        y_pos = lv_obj_get_height(scr) - PADDLE_HEIGHT;

    if (player == PLAYER_LEFT) {
        x_pos = PADDLE_MARGIN;
    } else {
        x_pos = lv_obj_get_width(scr) - PADDLE_WIDTH - PADDLE_MARGIN;
    }

    lv_obj_t ** paddle_obj = (player == PLAYER_LEFT) ? &paddle_left : &paddle_right;

    if (*paddle_obj == NULL) {
        *paddle_obj = lv_obj_create(scr);
        lv_obj_set_size(*paddle_obj, PADDLE_WIDTH, PADDLE_HEIGHT);
        lv_obj_set_style_bg_color(*paddle_obj, lv_color_white(), 0);
        lv_obj_set_style_border_width(*paddle_obj, 0, 0);
        lv_obj_set_style_radius(*paddle_obj, 0, 0);
    }

    lv_obj_set_pos(*paddle_obj, x_pos, y_pos);
}

static void update_scoreboard(void)
{
    char buf[8];

    snprintf(buf, sizeof(buf), "%d", score_left);
    lv_label_set_text(score_left_label, buf);

    snprintf(buf, sizeof(buf), "%d", score_right);
    lv_label_set_text(score_right_label, buf);
}

void example_lvgl_demo_ui(lv_display_t * disp)
{
    scr = lv_display_get_screen_active(disp);

    // Set rotation
    lv_disp_set_rotation(disp, LV_DISP_ROTATION_90);

    // Black background
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);

    lv_coord_t scr_w = lv_obj_get_width(scr);
    lv_coord_t scr_h = lv_obj_get_height(scr);

    // Create border if missing
    if (border == NULL) {
        border = lv_obj_create(scr);
        lv_obj_set_size(border, scr_w, scr_h);
        lv_obj_set_style_bg_color(border, lv_color_black(), 0);
        lv_obj_set_style_border_color(border, lv_color_white(), 0);
        lv_obj_set_style_border_width(border, BORDER_WIDTH, 0);
        lv_obj_set_style_radius(border, 0, 0);
        lv_obj_clear_flag(border, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_move_background(border);
    }

    // Create separator line if missing
    if (separator_line == NULL) {
        separator_line = lv_obj_create(scr);
        lv_obj_set_size(separator_line, 2, scr_h - 2 * BORDER_WIDTH);
        lv_obj_set_style_bg_color(separator_line, lv_color_white(), 0);
        lv_obj_set_style_border_width(separator_line, 0, 0);
        lv_obj_clear_flag(separator_line, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_align(separator_line, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_foreground(separator_line);
    }

    // Create ball if missing
    if (ball == NULL) {
        ball = lv_obj_create(scr);
        lv_obj_set_size(ball, BALL_SIZE, BALL_SIZE);
        lv_obj_set_style_bg_color(ball, lv_color_white(), 0);
        lv_obj_set_style_radius(ball, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_border_width(ball, 0, 0);
    }
    lv_obj_set_pos(ball, (scr_w - BALL_SIZE) / 2, (scr_h - BALL_SIZE) / 2);

    // Create scoreboard labels if missing
    if (score_left_label == NULL) {
        score_left_label = lv_label_create(scr);
        lv_label_set_text(score_left_label, "0");
        lv_obj_set_style_text_color(score_left_label, lv_color_white(), 0);
        lv_obj_set_style_text_font(score_left_label, SCORE_FONT, 0);
        lv_obj_align(score_left_label, LV_ALIGN_TOP_MID, -40, 10);
    }
    if (score_right_label == NULL) {
        score_right_label = lv_label_create(scr);
        lv_label_set_text(score_right_label, "0");
        lv_obj_set_style_text_color(score_right_label, lv_color_white(), 0);
        lv_obj_set_style_text_font(score_right_label, SCORE_FONT, 0);
        lv_obj_align(score_right_label, LV_ALIGN_TOP_MID, 40, 10);
    }

    update_scoreboard();

    // Draw paddles with example positions
    paddle(scr_h / 4, PLAYER_LEFT);
    paddle(scr_h * 3 / 4 - PADDLE_HEIGHT, PLAYER_RIGHT);
}
