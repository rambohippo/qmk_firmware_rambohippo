#ifndef RAMBOHIPPO_FUNCTIONS
#define RAMBOHIPPO_FUNCTIONS
#include "default_keyboard.h"

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
#define LN_DKFW LGUI(LCTL(KC_DOWN))     // Pop OS - Next Workspace
#define LN_DKBK LGUI(LCTL(KC_UP))       // Pop OS - Previous Workspace
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

#endif