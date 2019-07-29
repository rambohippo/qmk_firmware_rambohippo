#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
    #include "lufa.h"
    #include "split_util.h"
#endif
#ifdef SSD1306OLED
    #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;
extern uint8_t is_master;
bool is_alt_tab_active = false;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


enum lily_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _ADJUST
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
#define LN_DKFW LCTL(LALT(KC_RGHT))     // Linux - Next Desktop
#define LN_DKBK LCTL(LALT(KC_LEFT))     // Linux - Previous Desktop
#define WN_DKFW LCTL(LGUI(KC_RGHT))     // Windows - Next Desktop
#define WN_DKBK LCTL(LGUI(KC_LEFT))     // Windows - Previous Desktop
#define WN_DKNW LCTL(LGUI(KC_D))        // Windows - New Desktop
#define WN_DKCL LCTL(LGUI(KC_F4))       // Windows - Close Desktop
#define CTAB_FW LCTL(KC_TAB)            // Ctrl-Tab
#define CTAB_BK LSFT(LCTL(KC_TAB))      // Shift-Ctrl-Tab


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui |Numpad|LOWER | /Space  /       \Enter \  |RAISE | Bksp | RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,   KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
    KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,   KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,  KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                              KC_LGUI, NUMPAD, LOWER, KC_SPC,   KC_ENT,   RAISE,   KC_BSPC, KC_RALT \
),

/* LOWER - Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |AltTab|      |  Up  |      |PageUp|      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Left | Down | Right|PageDn|AltTab|-------.    ,-------| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|  F5   |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      | Enter| Bksp |-------|    |-------|      |      | Home | End  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | ---- | /       /       \Space \  | Raise|BackSP|      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    ALT_TAB, _______, KC_UP,   _______, KC_PGUP, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, ALT_TAB,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    KC_LSFT, _______, _______, _______, KC_ENT,  KC_BSPC, KC_F5,   _______, _______, _______, KC_HOME, KC_END,  _______, _______,\
                               _______, _______, _______, _______, KC_SPC,  RAISE,   KC_BSPC, _______ \
),

/* RAISE - Symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | Mute |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |                    |   ~  |   `  |   -  |   \  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   #  |   $  |   (  |   )  |   *  |-------.    ,-------|      |   +  |   =  |   _  |      |Vol Up|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   %  |   ^  |   [  |   ]  |   &  |-------|    |-------|      |   '  |   "  |   .  |      |Vol Dn|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | Lower| / Space /       \      \  | ---- |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_MUTE, \
    _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                   KC_TILD, KC_GRV,  KC_MINS, KC_BSLS, _______, _______, \
    KC_CAPS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR,                   _______, KC_PLUS, KC_EQL,  KC_UNDS, _______, KC_VOLU, \
    KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, _______, _______, _______, KC_QUOT, KC_DQUO, _______, _______, KC_VOLD,\
                               _______, _______, LOWER,   KC_SPC,  _______, _______, _______, _______ \
),

/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |   /  |   *  |   =  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | STab |  Up  | Tab  |      |      |                    |      |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |-------.    ,-------|      |   4  |   5  |   6  |   +  |SEnter|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShfit|      |      |      |      |      |-------|    |-------|      |   1  |   2  |   6  |      | Enter|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | ---- |      | /       /       \Space \  |   0  |   ,  |   .  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUMPAD] = LAYOUT( \
    _______, _______,   _______, _______, _______, _______,                   _______, _______, KC_PSLS, KC_PAST, KC_PEQL, _______, \
    _______, S(KC_TAB), KC_UP,   KC_TAB,  _______, _______,                   _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, \
    _______, KC_LEFT,   KC_DOWN, KC_RGHT, _______, _______,                   _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, S(KC_PENT), \
    KC_LSFT, _______,   _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, KC_PENT,\
                                 _______, _______, _______, _______, _______,  KC_P0,   KC_COMM, KC_PDOT \
),


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |WinDCL|                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |SC Tab| C Tab|WinDNW|-------.    ,-------| Mute |Vol Dn|Vol Up| Play |      |PrtScn|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|LinPre|LinNxt|WinPre|WinNxt|      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | ---- | /       /       \      \  | ---- |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
    _______, _______, _______, _______, _______, WN_DKCL,                   _______, _______, _______, _______, _______, KC_F12, \
    _______,  _______, _______, CTAB_BK, CTAB_FW, WN_DKNW,                   KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, _______, KC_PSCR, \
    KC_LSFT, LN_DKBK, LN_DKFW, WN_DKBK, WN_DKFW, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                               _______, _______, _______, _______, _______, _______, _______, _______ \
)

/* BLANK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
[_BLANK] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                               _______, _______, _______, _______, _______, _______, _______, _______ \
)
*/

};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        matrix_write_ln(matrix, read_keylogs());
        //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        //matrix_write_ln(matrix, read_host_led_state());
        //matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
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
