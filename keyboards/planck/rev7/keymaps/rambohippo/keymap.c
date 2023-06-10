/* Copyright 2015-2023 Jack Humbert
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

bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _ADJUST
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    ALT_TAB,
    CTAB_FW,
    CTAB_BK,
    EXDTVAL
};

#define NUMPAD MO(_NUMPAD)
#define LN_DKFW LCTL(LALT(KC_RGHT))     // Linux - Next Desktop
#define LN_DKBK LCTL(LALT(KC_LEFT))     // Linux - Previous Desktop
#define WN_DKFW LCTL(LGUI(KC_RGHT))     // Windows - Next Desktop
#define WN_DKBK LCTL(LGUI(KC_LEFT))     // Windows - Previous Desktop
#define WN_DKNW LCTL(LGUI(KC_D))        // Windows - New Desktop
#define WN_DKCL LCTL(LGUI(KC_F4))       // Windows - Close Desktop
#define GUI_TAB LGUI(KC_TAB)            // Gui-Tab
#define KC_TERM LGUI(KC_T)              // Super-T - Opens Terminal
#define BROWSER LGUI(KC_3)              // Gui-3 - Windows - Opens browser
#define FILES LGUI(KC_E)                // Gui-E - Opens file browser

void ctrl_tab_register(bool *is_ctrl_registered) {
    if (*is_ctrl_registered) return;

    register_code(KC_LEFT_CTRL);
    *is_ctrl_registered = true;
}

void ctrl_tab_unregister(bool *is_ctrl_registered) {
    if (!*is_ctrl_registered) return;

    unregister_code(KC_LEFT_CTRL);
    *is_ctrl_registered = false;
}

void alt_tab_register(bool *is_alt_registered) {
    if (*is_alt_registered) return;

    register_code(KC_LEFT_ALT);
    *is_alt_registered = true;
}

void alt_tab_unregister(bool *is_alt_registered) {
    if (!*is_alt_registered) return;

    unregister_code(KC_LEFT_ALT);
    *is_alt_registered = false;
}

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Gui  | Ctrl | Alt  |Numpad| Lower| Space| Enter| Raise| Ctrl | Left | Right| Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LGUI, KC_LCTL, KC_LALT, NUMPAD,  TL_LOWR, KC_SPC,  KC_ENT,  TL_UPPR, KC_RCTL, KC_LEFT, KC_RGHT, KC_ESC
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |GuiTab|SC Tab| C Tab|PageUp|PageDn|AltTab| Left | Down |  Up  | Right|      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |ExDtVl|CtlTab| Term | Enter| Bksp |      | Home | End  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F5  |Browse|      | Files| ---- |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    GUI_TAB, CTAB_BK, CTAB_FW, KC_PGUP, KC_PGDN, ALT_TAB, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_DEL,
    _______, EXDTVAL, _______, KC_TERM, KC_ENT,  KC_BSPC, _______, _______, KC_HOME, KC_END,  _______, _______,
    KC_F5,   BROWSER, _______, FILES,   _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   {  |   }  |   |  |      |      |   -  |   \  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |   #  |   $  |   (  |   )  |   *  |      |   +  |   -  |   _  |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   &  |      |   '  |   "  |   ~  |   `  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RGB  |RGBMOD| HUE+ | HUE- |      |      |      | ---- | Vol- | Vol+ | Play | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, KC_MINS, KC_BSLS, _______, _______,
    KC_CAPS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, _______, KC_PLUS, KC_EQL,  KC_UNDS, _______, KC_DEL,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, _______, KC_QUOT, KC_DQUO, KC_TILD, KC_GRV,  _______,
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Up  |      |      |      |   =  |   7  |   8  |   9  |   -  |numlock|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Delete| Left | Down | Right|      |      |   *  |   4  |   5  |   6  |   +  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- |      |      |      |   0  |   ,  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    _______, _______, KC_UP,   _______, _______, _______, KC_PEQL, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_NUM,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_PSLS, KC_P1,   KC_P2,   KC_P3,   _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_COMM, KC_PDOT, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |PrtScn|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |SC Tab| C Tab|WinDNW|      |      |      |      |      | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |LinPre|LinNxt|WinPre|WinNxt|WinDCL|      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | ---- |      |      | ---- |      |      |      | Reset|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, CTAB_BK, CTAB_FW, WN_DKNW, _______, _______, _______, _______, _______, KC_F12,
    _______, LN_DKBK, LN_DKFW, WN_DKBK, WN_DKFW, WN_DKCL, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT
)

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_ADJUST] = LAYOUT_planck_grid(
//     _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
//     _______, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______,
//     _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// )

};
/* clang-format on */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case TL_LOWR:
            // On key release, release keys for alt-tab + ctrl-tab
            if (!record->event.pressed) {
                alt_tab_unregister(&is_alt_tab_active);
                ctrl_tab_unregister(&is_ctrl_tab_active);
            }
            return true;
            break;
        case ALT_TAB:
            if (record->event.pressed) {
                alt_tab_register(&is_alt_tab_active);
                ctrl_tab_unregister(&is_ctrl_tab_active);
                tap_code(KC_TAB);
            }
            break;
        case CTAB_FW:
            if (record->event.pressed) {
                ctrl_tab_register(&is_ctrl_tab_active);
                alt_tab_unregister(&is_alt_tab_active);
                tap_code(KC_TAB);
            }
            break;
        case CTAB_BK:
            if (record->event.pressed) {
                ctrl_tab_register(&is_ctrl_tab_active);
                alt_tab_unregister(&is_alt_tab_active);
                tap_code16(LSFT(KC_TAB));
            }
            break;
        case EXDTVAL:
            if (record->event.pressed) {
                tap_code(KC_LEFT_ALT);
                tap_code(KC_A);
                tap_code(KC_V);
                tap_code(KC_V);
            }
            break;
    }
    return true;
}

/* clang-format off */
float melody[8][2][2] = {
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}},
};
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307	

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    cancel_deferred_exec(tokens[index]);
    if (clockwise) {
        melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
        audio_play_melody(&melody[index], 2, false);
    } else {
        melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
        audio_play_melody(&melody[index], 2, false);
    }
    tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
    return false;
}