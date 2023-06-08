/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

extern keymap_config_t keymap_config;
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
    LOWER,
    RAISE,
    ADJUST,
    ALT_TAB,
    CTRLTAB,
    EXDTVAL
};

#define NUMPAD MO(_NUMPAD)
#define ADJUST MO(_ADJUST)
#define LN_DKFW LCTL(LALT(KC_RGHT))     // Linux - Next Desktop
#define LN_DKBK LCTL(LALT(KC_LEFT))     // Linux - Previous Desktop
#define WN_DKFW LCTL(LGUI(KC_RGHT))     // Windows - Next Desktop
#define WN_DKBK LCTL(LGUI(KC_LEFT))     // Windows - Previous Desktop
#define WN_DKNW LCTL(LGUI(KC_D))        // Windows - New Desktop
#define WN_DKCL LCTL(LGUI(KC_F4))       // Windows - Close Desktop
#define GUI_TAB LGUI(KC_TAB)            // Gui-Tab
#define CTAB_FW LCTL(KC_TAB)            // Ctrl-Tab
#define CTAB_BK LSFT(LCTL(KC_TAB))      // Shift-Ctrl-Tab
#define KC_TERM LGUI(KC_T)              // Super-T - Opens Terminal
#define BROWSER LGUI(KC_3)              // Gui-3 - Windows - Opens browser
#define FILES LGUI(KC_E)                // Gui-E - Opens file browser

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Gui  | Ctrl | Alt  |Numpad|Lower | Space| Enter| Raise| Ctrl | Left | Right| Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LGUI, KC_LCTL, KC_LALT, NUMPAD,  LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_RCTL, KC_LEFT, KC_RGHT, KC_ESC
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
    _______, EXDTVAL, CTRLTAB, KC_TERM, KC_ENT,  KC_BSPC, _______, _______, KC_HOME, KC_END,  _______, _______,
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
 * |      |      |      |      |      |      |      | ---- | Vol- | Vol+ |      | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, KC_MINS, KC_BSLS, _______, _______,
    KC_CAPS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, _______, KC_PLUS, KC_EQL,  KC_UNDS, _______, KC_DEL,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, _______, KC_QUOT, KC_DQUO, KC_TILD, KC_GRV,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______, KC_MUTE
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Up  |      |      |      |   =  |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Delete| Left | Down | Right|      |      |   *  |   4  |   5  |   6  |   +  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- |      |      |      |   0  |   ,  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    _______, _______, KC_UP,   _______, _______, _______, KC_PEQL, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_DEL,
    _______, _______, _______, _______, _______, _______, KC_PSLS, KC_P1,   KC_P2,   KC_P3,   _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_COMM, KC_PDOT, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)
*/

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |PrtScn|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |SC Tab| C Tab|WinDNW|      |      |      |      |      | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |LinPre|LinNxt|WinPre|WinNxt|WinDCL|      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Reset|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, CTAB_BK, CTAB_FW, WN_DKNW, _______, _______, _______, _______, _______, KC_F12,
    _______, LN_DKBK, LN_DKFW, WN_DKBK, WN_DKFW, WN_DKCL, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET
),

/* Blank
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
[_BLANK] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
*/

};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                if (is_alt_tab_active) {
                    unregister_code(KC_LALT);
                    is_alt_tab_active = false;
                }
                if (is_ctrl_tab_active) {
                    unregister_code(KC_LCTL);
                    is_ctrl_tab_active = false;
                }
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CTRLTAB:
            if (record->event.pressed) {
                if (!is_ctrl_tab_active) {
                    is_ctrl_tab_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case EXDTVAL:
            if (record->event.pressed) {
                tap_code(KC_LALT);
                tap_code(KC_A);
                tap_code(KC_V);
                tap_code(KC_V);
            }
            break;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
#else
            tap_code(KC_PGUP);
#endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
