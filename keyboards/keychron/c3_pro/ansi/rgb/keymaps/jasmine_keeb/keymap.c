/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
// Disable RGB effects
// #undef RGBLIGHT_ANIMATIONS
// #define RGB_DISABLE_WHEN_USB_SUSPENDED true
// #define RGBLIGHT_ENABLE false
// #define RGB_MATRIX_ENABLE false

enum layers{
  BASE,
  FN,
};

#define KC_TASK G(KC_TAB)
#define KC_FLXP G(KC_E)

// Define a custom keycode for the macro
enum custom_keycodes {
    EMAL_MACRO = SAFE_RANGE,
    LOVE_MACRO,
    HAMM_MACRO,
    SLIM_MACRO
};

uint16_t rgb_timer = 0;

// Handle the custom keycode in process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EMAL_MACRO:
            if (record->event.pressed) {
                // Replace this with your email address
                SEND_STRING("Jasmineaizely@gmail.com");
            }
            return false;
        case LOVE_MACRO:
            if (record->event.pressed) {
                SEND_STRING("i<3u");
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_PINK);
                rgb_timer = timer_read();
            }
            return false;
        case HAMM_MACRO:
            if (record->event.pressed) {
                SEND_STRING("okay, okay, lets kill this guy with hammers");
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_RED);
                rgb_timer = timer_read();
            }
            return false;
        case SLIM_MACRO:
            if (record->event.pressed) {
                SEND_STRING("much respect for my big slime");
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_GREEN);
                rgb_timer = timer_read();
            }
            return false;
        case DM_REC1:
            if (record->event.pressed) {
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_BLUE);
            }
            return true;
        case DM_PLY1:
            if (record->event.pressed) {
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_BLUE);
                rgb_timer = timer_read();
            }
            return true;
        case DM_REC2:
            if (record->event.pressed) {
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_YELLOW);
            }
            return true;
        case DM_PLY2:
            if (record->event.pressed) {
                rgb_matrix_enable();
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(HSV_YELLOW);
                rgb_timer = timer_read();
            }
            return true;
        case DM_RSTP:
            rgb_matrix_disable();
            return true;
        default:
            return true;
    }
}

void matrix_scan_user(void) {
    // Turn off RGB after 500ms
    if (rgb_timer && timer_elapsed(rgb_timer) > 1000) {
        rgb_matrix_disable();
        rgb_timer = 0;
    }
}

// Disable RGB on keyboard init
void keyboard_post_init_user(void) {
    rgb_matrix_disable();
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,   KC_PSCR,KC_SCROLL_LOCK,KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,    KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,   KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN),KC_APP,    KC_RCTL,KC_LEFT,  KC_DOWN,  KC_RGHT ),

    [FN] = LAYOUT_tkl_ansi(
        LOVE_MACRO,           DM_PLY1,  DM_PLY2,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RGB_MOD,
        _______,  DM_REC1,  DM_REC2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  DM_RSTP,  _______,
        _______,  _______,  BL_DOWN,  _______,  _______,  _______,  HAMM_MACRO,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  EMAL_MACRO,  _______,  _______,  _______,              _______,            _______,
        SLIM_MACRO,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

};