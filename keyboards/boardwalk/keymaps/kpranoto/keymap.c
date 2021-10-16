#include QMK_KEYBOARD_H
#include "keymap.h"
#include "config.h"

enum my_keycodes { 
    DELAYED_PGUP = SAFE_RANGE,
    DELAYED_PGDN,
    DELAYED_HOME,
    DELAYED_END
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_2x2u(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, DELAYED_PGUP, KC_LBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, DELAYED_PGDN, KC_RBRC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, DELAYED_HOME, DELAYED_END, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, MO(2), KC_ENT, KC_SPC, MO(1), MO(2), KC_RGUI, KC_RCTL, KC_GRV),
	[1] = LAYOUT_ortho_2x2u(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, C(G(KC_Q)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO),
	[2] = LAYOUT_ortho_2x2u(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, C(G(KC_Q)), KC_NO, RGB_HUI, RGB_VAI, RGB_SAI, RGB_SPI, RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_NO, RGB_HUD, RGB_VAD, RGB_SAD, RGB_SPD, RGB_RMOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_MRWD, KC_MFFD, KC_MSTP, KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DELAYED_PGDN:
            return process_delayed(KC_PGDN, record);
        case DELAYED_PGUP:
            return process_delayed(KC_PGUP, record);
        case DELAYED_HOME:
            return process_delayed(KC_HOME, record);
        case DELAYED_END:
            return process_delayed(KC_END, record);
        default:
            return true; // Process all other keycodes normally
    }
}

uint16_t k_timer = 0;
bool process_delayed(uint16_t actual, keyrecord_t *record) {

    if (record->event.pressed) {
        k_timer = timer_read();
    } 

    if (timer_elapsed(k_timer) > DELAY) {
        tap_code16(actual);
        k_timer = 0;
    }

    return false;
}
