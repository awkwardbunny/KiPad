// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ A │ B │ C │ D │
     * └───┴───┴───┴───┘
     * ┌───┬───┬───┬───┐
     * │Num│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │ 0     │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_6x4(
        TO(0),   TO(1),   TO(2),   TO(3),
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
    ),
    [1] = LAYOUT_numpad_6x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_VOLU, LM_BRIU,   KC_NO,
        KC_MPRV, KC_MSTP, KC_MNXT,
        KC_NO,   KC_VOLD, LM_BRID,   KC_MPLY,
        KC_MUTE,          KC_NO
    ),
    [2] = LAYOUT_numpad_6x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,            KC_NO
    ),
    [3] = LAYOUT_numpad_6x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_SPC,           KC_NO
    )
};

static unsigned char layer = 2;
static bool numlock = false;
// static uint8_t brightness = 255;

static void update_leds(void) {
    rgb_matrix_set_color_all(RGB_BLACK);
    if(layer == 0) {
        rgb_matrix_set_color(0, RGB_BLUE);
    } else if(layer == 1) {
        rgb_matrix_set_color(1, RGB_GREEN);

        rgb_matrix_set_color(9, 0x20, 0xCC, 0x20);
        rgb_matrix_set_color(12, 0x20, 0xCC, 0x20);
        rgb_matrix_set_color(13, RGB_ORANGE);
        rgb_matrix_set_color(14, 0x20, 0xCC, 0x20);
        rgb_matrix_set_color(16, 0x20, 0xCC, 0x20);
        rgb_matrix_set_color(18, RGB_GREEN);
        rgb_matrix_set_color(19, RGB_RED);
    } else if(layer == 2) {
        rgb_matrix_set_color(2, RGB_ORANGE);
    } else if(layer == 3) {
        rgb_matrix_set_color(3, RGB_RED);
    }

    if(numlock) {
        rgb_matrix_set_color(4, RGB_BLUE);
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_set_color_all(RGB_BLACK);
    update_leds();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    layer = get_highest_layer(state);
    // update_leds();
    return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        numlock = led_state.num_lock;
        // update_leds();
    }
    return res;
}

bool rgb_matrix_indicators_kb(void) {
    bool res = rgb_matrix_indicators_user();
    update_leds();
    return res;
}