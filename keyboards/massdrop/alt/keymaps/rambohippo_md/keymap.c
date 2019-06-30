#include QMK_KEYBOARD_H

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase                                   //Working
    L_BRD,              //LED Brightness Decrease                                   //Working
    L_PTN,              //LED Pattern Select Next                                   //Working
    L_PTP,              //LED Pattern Select Previous                               //Working
    L_PSI,              //LED Pattern Speed Increase                                //Working
    L_PSD,              //LED Pattern Speed Decrease                                //Working
    L_T_MD,             //LED Toggle Mode                                           //Working
    L_T_ONF,            //LED Toggle On / Off                                       //Broken
    L_ON,               //LED On                                                    //Broken
    L_OFF,              //LED Off                                                   //Broken
    L_T_BR,             //LED Toggle Breath Effect                                  //Working
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction                    //Working
    U_T_AGCR,           //USB Toggle Automatic GCR control                          //Working
    DBG_TOG,            //DEBUG Toggle On / Off                                     //
    DBG_MTRX,           //DEBUG Toggle Matrix Prints                                //
    DBG_KBD,            //DEBUG Toggle Keyboard Prints                              //
    DBG_MOU,            //DEBUG Toggle Mouse Prints                                 //
    MD_BOOT,            //Restart into bootloader after hold timeout                //Working
    L_I_N,              //LED instruction preset next
    L_I_P,              //LED instruction preset previous
    L_SC_N,             //LED Pattern scroll next
    L_SC_P,             //LED pattern scroll previous
    L_T_UND,            //LED Toggle Underglow
    L_T_GCM             //LED Toggle Game Color Mode and Layer
};

// Layers
enum alt_layers {
    _BASE,
    _GAME,
    _MODS,
    _NAV,
    _NUMS,
    _SYMB
};

#define TG_NKRO MAGIC_TOGGLE_NKRO       //Toggle 6KRO / NKRO mode
#define FN MO(_MODS)
#define SYMB MO(_SYMB)

// #define CAPS_TAP LCTL_T(KC_CAPS)
#define CAPS_MOD LT(_NUMS, KC_CAPS)     // Hold for _NUMS layer, tap for Caps Lock
// #define ESC_MOD LT(_NUMS, KC_ESC)
#define ESC_TAP LCTL_T(KC_ESC)          // Hold for L-CTRL, tap for esc
#define SPACE_MOD LT(_NAV, KC_SPC)      // Hold for _NAV layer, tap for Space

#define DESK_BK LCTL(LALT(KC_LEFT))     // Linux - Previous desktop
#define DESK_FW LCTL(LALT(KC_RIGHT))    // Linux - Next desktop
#define ATAB_BK LSFT(LALT(KC_TAB))
#define ATAB_FW LALT(KC_TAB)
#define CTAB_BK LSFT(LCTL(KC_TAB))
#define CTAB_FW LCTL(KC_TAB)

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        CAPS_MOD,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        ESC_TAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            SPACE_MOD,                          SYMB,    FN,      KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_GAME] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, FN,      KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_MODS] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   _______, KC_TILD, _______, _______, U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END, \
        L_T_PTD, L_I_P,   L_BRD,   L_I_N,   _______, _______, _______, _______, _______, _______, _______, _______,          L_T_GCM, KC_VOLU, \
        L_T_UND, L_T_MD,  L_T_ONF, L_PTP,   L_PTN,   MD_BOOT, TG_NKRO, _______, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            KC_MPLY,                            _______, _______, KC_HOME, KC_PGDN, KC_END  \
    ),
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, CTAB_BK, CTAB_FW, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______, \
        _______, _______, _______, ATAB_BK, ATAB_FW, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            DESK_BK, DESK_FW, _______, _______, _______  \
    ),
    [_NUMS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_PMNS, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PPLS, _______,          KC_ENT, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,          _______, _______, \
        _______, _______, _______,                            KC_0,                               KC_PDOT, KC_ENT,  _______, _______, _______  \
    ),
    [_SYMB] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;

        // Custom keycodes
        case L_I_N:
            if (record->event.pressed) {
                (led_instruction_id == led_instruction_count - 1) ? led_instruction_id = 0 : led_instruction_id++;
                set_led_animation_id(led_default_rotate_pattern[led_instruction_id]);
            }
            return false;
        case L_I_P:
            if (record->event.pressed) {
                (led_instruction_id == 0) ? led_instruction_id = led_instruction_count - 1 : led_instruction_id--;
                set_led_animation_id(led_default_rotate_pattern[led_instruction_id]);
            }
            return false;
        case L_T_UND:
            if (record->event.pressed) {
                switch (led_lighting_mode) {
                    case (LED_MODE_NORMAL):
                        led_lighting_mode = LED_MODE_KEYS_ONLY;
                        return false;
                    case (LED_MODE_KEYS_ONLY):
                        led_lighting_mode = LED_MODE_NORMAL;
                        return false;
                    case (LED_MODE_NON_KEYS_ONLY):
                        led_lighting_mode = LED_MODE_INDICATORS_ONLY;
                        return false;
                    case (LED_MODE_INDICATORS_ONLY):
                        led_lighting_mode = LED_MODE_NON_KEYS_ONLY;
                        return false;
                    default:
                        return true;
                }
            }
            return false;
        case L_T_GCM:
            if (record->event.pressed) {
                if (led_game_colors) {
                    set_single_persistent_default_layer(_BASE);
                } else {
                    set_single_persistent_default_layer(_GAME);
                }
                led_game_colors = !led_game_colors;
            }
            return true;
        /*
        case L_SC_N:
            if (record->event.pressed) {
                led_animation_orientation++;
                if (led_animation_orientation > LED_SCROLL_MAX_INDEX) led_animation_orientation = LED_SCROLL_HORIZ;
            }
            return false;
        case L_SC_P:
            if (record->event.pressed) {
                if (led_animation_orientation == 0) led_animation_orientation = LED_SCROLL_MAX_INDEX;
                led_animation_orientation--;
            }
            return false;
        */
        default:
            return true; //Process all other keycodes normally
    }
}

/*
led_instruction_t led_instructions[] = {
    //LEDs are normally inactive, no processing is performed on them
    //Flags are used in matching criteria for an LED to be active and indicate how to color it
    //Flags can be found in tmk_core/protocol/arm_atsam/led_matrix.h (prefixed with LED_FLAG_)
    //LED IDs can be found in config_led.h in the keyboard's directory
    //Examples are below

    //All LEDs use the user's selected pattern (this is the factory default)
    // { .flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN },

    //Specific LEDs use the user's selected pattern while all others are off
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN, .id0 = 0xFFFFFFFF, .id1 = 0xAAAAAAAA, .id2 = 0x55555555, .id3 = 0x11111111 },

    //Specific LEDs use specified RGB values while all others are off
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 0xFF, .id1 = 0x00FF, .id2 = 0x0000FF00, .id3 = 0xFF000000, .r = 75, .g = 150, .b = 225 },

    //All LEDs use the user's selected pattern
    //On layer 1, all key LEDs (except the top row which keeps active pattern) are red while all edge LEDs are green
    //When layer 1 is active, key LEDs use red    (id0  32 -  16: 1111 1111 1111 1111 1000 0000 0000 0000 = 0xFFFF8000) (except top row 15 - 1)
    //When layer 1 is active, key LEDs use red    (id1  64 -  33: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
    //When layer 1 is active, key LEDs use red    (id2  67 -  65: 0000 0000 0000 0000 0000 0000 0000 0111 = 0x00000007)
    //When layer 1 is active, edge LEDs use green (id2  95 -  68: 1111 1111 1111 1111 1111 1111 1111 1000 = 0xFFFFFFF8)
    //When layer 1 is active, edge LEDs use green (id3 105 -  96: 0000 0000 0000 0000 0000 0011 1111 1111 = 0x000003FF)
    // { .flags = LED_FLAG_USE_ROTATE_PATTERN },
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFF8000, .id1 = 0xFFFFFFFF, .id2 = 0x00000007, .r = 255, .layer = 1 },
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id2 = 0xFFFFFFF8, .id3 = 0x000003FF, .g = 127, .layer = 1 },

    //All key LEDs use red while edge LEDs use the active pattern
    //All key LEDs use red     (id0  32 -   1: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
    //All key LEDs use red     (id1  64 -  33: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
    //All key LEDs use red     (id2  67 -  65: 0000 0000 0000 0000 0000 0000 0000 0111 = 0x00000007)
    //Edge uses active pattern (id2  95 -  68: 1111 1111 1111 1111 1111 1111 1111 1000 = 0xFFFFFFF8)
    //Edge uses active pattern (id3 105 -  96: 0000 0000 0000 0000 0000 0011 1111 1111 = 0x000003FF)
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0x00000007, .r = 255 },
    // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN , .id2 = 0xFFFFFFF8, .id3 = 0x000003FF },

    // Custom Colors
    { .flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .layer = 0, .id0 = 2684297214, .id1 = 545252351, .id2 = 4261416832, .id3 = 7, .r = 255, .g = 255, .b = 255}, // white
    { .flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .layer = 0, .id0 = 1610670081, .id1 = 3749714944, .id2 = 33550463, .id3 = 504, .r = 24, .g = 215, .b = 204}, // teal
    { .flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .layer = 1, .id0 = 2684297214, .id1 = 545252351, .id2 = 4261416832, .id3 = 7, .r = 255, .g = 255, .b = 255}, // white
    { .flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .layer = 1, .id0 = 1610670081, .id1 = 3749714944, .id2 = 33550463, .id3 = 504, .r = 24, .g = 215, .b = 204}, // teal

    //end must be set to 1 to indicate end of instruction set
     { .end = 1 }
};
*/

led_instruction_t led_instructions_white_and_teal[] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 2684297214, .id1 = 545252351, .id2 = 4261416832, .id3 = 7, .r = 255, .g = 255, .b = 255 }, // white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 1610670081, .id1 = 3749714944, .id2 = 33550463, .id3 = 504, .r = 24, .g = 215, .b = 204 }, // teal
    { .end = 1 }
};

led_instruction_t led_instructions_miami[] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 2684297214, .id1 = 545252351, .id2 = 4261416832, .id3 = 7, .r = 46, .g = 255, .b = 255 }, // blue
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 1610670081, .id1 = 3749714944, .id2 = 33550463, .id3 = 504, .r = 254, .g = 109, .b = 188 }, // pink
    { .end = 1 }
};

led_instruction_t led_instructions_white_and_pattern_mods[] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 2684297214, .id1 = 545252351, .r = 255, .g = 255, .b = 255 }, // white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN, .id0 = 1610670081, .id1 = 3749714944, .id2 = 4294967295, .id3 = 511 }, // pattern
    { .end = 1 }
};

led_instruction_t led_instructions_rainbow[] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN, .id0 = 4294967295, .id1 = 4294967295, .id2 = 4294967295, .id3 = 511 },
    { .end = 1 }
};

led_instruction_t led_game_instructions[] = {
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 2147614721, .id1 = 16777219, .id2 = 7, .r = 255, .g = 0, .b = 0 }, // Red wasd, arrow keys, and esc
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 2147352448, .id1 = 2063593468, .r = 255, .g = 255, .b = 255 }, // White everything else
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 126, .id1 = 67112960, .r = 24, .g = 215, .b = 204 }, // Teal numbers and some modifiers
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id1 = 2147483648, .r = 0, .g = 0, .b = 255 }, // Teal Fn key
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN, .id2 = 4294967288, .id3 = 511 }, // Pattern on underglow
    { .end = 1 }
};

void *led_instruction_list[] = {
    led_instructions_white_and_teal,
    led_instructions_miami,
    led_instructions_white_and_pattern_mods,
    led_instructions_rainbow
};

void *led_game_instruction_list[] = {
    led_game_instructions,
    led_game_instructions,
    led_game_instructions,
    led_game_instructions
};

const uint8_t led_instruction_count = sizeof(led_instruction_list) / sizeof(led_instruction_list[0]);

uint8_t led_default_rotate_pattern[4] = {
    0, 0, 1, 0
};

void rgb_matrix_init_user(void) {
    // Set which from led_instruction_list should be default
    uint8_t index = 1;
    led_instruction_id = index;
    set_led_animation_id(led_default_rotate_pattern[index]);
}

