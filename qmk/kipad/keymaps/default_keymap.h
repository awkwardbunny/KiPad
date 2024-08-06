/* Copyright 2018 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,            KC_PDOT, KC_PENT
    ),
};

// bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
//     switch(keycode) {
//         case TO_0:
//         case
//     }
// }

bool invert = false;
unsigned char layer = 0;

static void update_leds(void){
    gpio_write_pin(GP26, !((layer == 0) ^ invert));
    gpio_write_pin(GP27, !((layer == 1) ^ invert));
    gpio_write_pin(GP28, !((layer == 2) ^ invert));
    gpio_write_pin(GP29, !((layer == 3) ^ invert));
}

void keyboard_post_init_user() {
    gpio_set_pin_output(GP26);
    gpio_set_pin_output(GP27);
    gpio_set_pin_output(GP28);
    gpio_set_pin_output(GP29);
    update_leds();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    layer = get_highest_layer(state);
    update_leds();
    return state;
}


bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
//     if(res) {
//         // gpio_write_pin sets the pin high for 1 and low for 0.
//         // In this example the pins are inverted, setting
//         // it low/0 turns it on, and high/1 turns the LED off.
//         // This behavior depends on whether the LED is between the pin
//         // and VCC or the pin and GND.
//         gpio_write_pin(B0, !led_state.num_lock);
//         gpio_write_pin(B1, !led_state.caps_lock);
//         gpio_write_pin(B2, !led_state.scroll_lock);
//         gpio_write_pin(B3, !led_state.compose);
//         gpio_write_pin(B4, !led_state.kana);
//     }
    if(res) {
        invert = !led_state.num_lock;
        update_leds();
    }
    return res;
}
