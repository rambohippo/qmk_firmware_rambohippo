#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
bool is_alt_tab_active = false;

enum nyquist_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _ADJUST     // Needs to be the last layer for tri-layer to work properly
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  ALT_TAB
};

// Keycode definitions
#define NUMPAD MO(_NUMPAD)
#define ESC_TAP LCTL_T(KC_ESC)          // Hold for L-CTRL, tap for esc
#define LN_DKFW LCTL(LALT(KC_RGHT))     // Linux - Next Desktop
#define LN_DKBK LCTL(LALT(KC_LEFT))     // Linux - Previous Desktop
#define WN_DKFW LCTL(LGUI(KC_RGHT))     // Windows - Next Desktop
#define WN_DKBK LCTL(LGUI(KC_LEFT))     // Windows - Previous Desktop
#define WN_DKNW LCTL(LGUI(KC_D))        // Windows - New Desktop
#define WN_DKCL LCTL(LGUI(KC_F4))       // Windows - Close Desktop
#define ATAB_FW LALT(KC_TAB)            // Alt-Tab
#define ATAB_BK LSFT(LALT(KC_TAB))      // Shift-Alt-Tab
#define CTAB_FW LCTL(KC_TAB)            // Ctrl-Tab
#define CTAB_BK LSFT(LCTL(KC_TAB))      // Shift-Ctrl-Tab

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Gui  | Ctrl | Alt  |Numpad| Lower| Space|  | Enter| Raise| Ctrl | Left |  Up  | Enter|
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT , \
  KC_LGUI, KC_LCTL, KC_LALT, NUMPAD,  LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_RCTL, KC_LEFT, KC_RGHT,   KC_ENT \
),

/* Lower
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |AltTab|      |  Up  |      |PageUp|      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      | Left | Down | Right|PageDn|AltTab|  | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|      |      |      | Enter| Bksp |  |      |      | Home | End  |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F5  |      |      |      | ---- |      |  | Space|      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_LOWER] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  ALT_TAB,  _______, KC_UP, _______,  KC_PGUP, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, ALT_TAB, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  KC_LSFT, _______, _______, _______, KC_ENT,  KC_BSPC, _______, _______, KC_HOME, KC_END,  _______, _______, \
  KC_F5,   _______, _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______ \
),

/* RAISE
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |      |      |      |      |      | Mute |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |  |   ~  |   `  |   -  |   \  |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Caps |   #  |   $  |   (  |   )  |   *  |  |      |   +  |   =  |   _  |      |Vol Up|
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   %  |   ^  |   [  |   ]  |   &  |  |      |   '  |   "  |      |      |Vol Dn|
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      | Space|  |      | ---- |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_RAISE] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, \
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, KC_GRV,  KC_MINS, KC_BSLS, _______, _______, \
  KC_CAPS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, _______, KC_PLUS, KC_EQL,  KC_UNDS, _______, KC_VOLU, \
  KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, _______, KC_QUOT, KC_DQUO, _______,  _______, KC_VOLD, \
  _______, _______, _______, _______, _______,  KC_SPC, _______, _______, _______, _______, _______, _______ \
),

/* NUMPAD - Arrows are not in a good location. Consider reworking left side
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |      |      |   /  |   *  |   =  | Del  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      | STab |  Up  |  Tab |      |      |  |      |   7  |   8  |   9  |   -  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      | Right| Down | Left |      |      |  |      |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |  |      |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | ---- |      |      |      |      |      |  | Space|   0  |   ,  |   .  | Enter|      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_NUMPAD] =  LAYOUT( \
  _______, _______,   _______,  _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PEQL, KC_DEL, \
  _______, S(KC_TAB), KC_UP,    KC_TAB,  _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_BSPC, \
  _______, KC_RGHT,   KC_DOWN,  KC_LEFT, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, \
  KC_LSFT, _______,   _______,  _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, \
  _______, _______,   _______,  _______, _______, _______, KC_SPC,  KC_P0,   KC_COMM, KC_PDOT, KC_PENT, _______ \
),

/* Adjust (Lower + Raise) - Media and Functions
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |SC Tab| C Tab|WinDCL|  |      |      |      |      |      |  F12 |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Del  |      |      |SA Tab| A TAb|WinDNW|  | Mute | Vol -| Vol +| Play |      |PrtScn|
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|LinPre|LinNxt|WinPre|WinNxt|      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      | ---- |      |  |      | ---- |      |      |      | Reset|
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  _______, _______, _______, CTAB_BK, CTAB_FW, WN_DKCL, _______, _______, _______, _______, _______, KC_F12, \
  KC_DEL,  _______, _______, ATAB_BK, ATAB_FW, WN_DKNW, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, _______, KC_PSCR, \
  KC_LSFT, LN_DKBK, LN_DKFW, WN_DKBK, WN_DKFW, _______,   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET \
)

/* BLANK
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 *
[_BLANK] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)
*/

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
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
    }
    return true;
}
