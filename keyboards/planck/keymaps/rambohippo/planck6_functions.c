#ifndef PLANCK6_FUNCTIONS
#define PLANCK6_FUNCTIONS
#include "quantum.h"
#include "muse.h"
#include "os_detection.h"

bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _MEDIA,
    _ADJUST
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    ALT_TAB,
    CTAB_FW,
    CTAB_BK,
    EXDTVAL,
    WORK_FW,
    WORK_BK,
    WORK_NW,
    WORK_CL,
    WORK_SH
};

#define NUMPAD MO(_NUMPAD)
#define MEDIA MO(_MEDIA)
#define LN_DKFW LGUI(LCTL(KC_DOWN))     // Pop OS - Next Workspace
#define LN_DKBK LGUI(LCTL(KC_UP))       // Pop OS - Previous Workspace
#define LN_WNFW LGUI(LSFT(KC_DOWN))     // Pop OS - Move window to next workspace
#define LN_WNBK LGUI(LSFT(KC_UP))       // Pop OS - Move window to previous workspace
#define WN_DKFW LCTL(LGUI(KC_RGHT))     // Windows - Next Desktop
#define WN_DKBK LCTL(LGUI(KC_LEFT))     // Windows - Previous Desktop
#define WN_DKNW LCTL(LGUI(KC_D))        // Windows - New Desktop
#define WN_DKCL LCTL(LGUI(KC_F4))       // Windows - Close Desktop
#define GUI_TAB LGUI(KC_TAB)            // Gui-Tab
#define LN_WORK LGUI(KC_D)              // Pop OS - Show workspaces
#define WN_WORK LGUI(KC_TAB)            // Windows - Show workspaces
#define KC_TERM LGUI(KC_T)              // Super-T - Opens Terminal
#define BROWSER LGUI(KC_3)              // Gui-3 - Windows - Opens browser
#define FILES LGUI(KC_E)                // Gui-E - Opens file browser
#define IDEA_DN LSFT(LALT(KC_DOWN))     // Intellij Idea - Move Line Down
#define IDEA_UP LSFT(LALT(KC_UP))       // Intellij Idea - Move Line Up

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

void next_workspace(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            tap_code16(LN_DKFW);
            break;
        case OS_WINDOWS:
        default:
            tap_code16(WN_DKFW);
            break;
    }
}

void previous_workspace(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            tap_code16(LN_DKBK);
            break;
        case OS_WINDOWS:
        default:
            tap_code16(WN_DKBK);
            break;
    }
}

void create_workspace(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            tap_code16(LN_DKFW);
            break;
        case OS_WINDOWS:
        default:
            tap_code16(WN_DKNW);
            break;
    }
}

void remove_workspace(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            tap_code16(LN_DKBK);
            break;
        case OS_WINDOWS:
        default:
            tap_code16(WN_DKCL);
            break;
    }
}

void show_workspaces(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            tap_code16(LN_WORK);
            break;
        case OS_WINDOWS:
        default:
            tap_code16(WN_WORK);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case TL_LOWR:
            // On key release, release keys for alt-tab + ctrl-tab
            if (!record->event.pressed) {
                alt_tab_unregister(&is_alt_tab_active);
                ctrl_tab_unregister(&is_ctrl_tab_active);
            }
            return true;
        case ALT_TAB:
            if (record->event.pressed) {
                alt_tab_register(&is_alt_tab_active);
                ctrl_tab_unregister(&is_ctrl_tab_active);
                tap_code(KC_TAB);
            }
            return false;
        case CTAB_FW:
            if (record->event.pressed) {
                ctrl_tab_register(&is_ctrl_tab_active);
                alt_tab_unregister(&is_alt_tab_active);
                tap_code(KC_TAB);
            }
            return false;
        case CTAB_BK:
            if (record->event.pressed) {
                ctrl_tab_register(&is_ctrl_tab_active);
                alt_tab_unregister(&is_alt_tab_active);
                tap_code16(LSFT(KC_TAB));
            }
            return false;
        case EXDTVAL:
            if (record->event.pressed) {
                tap_code(KC_LEFT_ALT);
                tap_code(KC_A);
                tap_code(KC_V);
                tap_code(KC_V);
            }
            return false;
        case WORK_FW:
            if (record->event.pressed) {
                next_workspace();
            }
            return false;
        case WORK_BK:
            if (record->event.pressed) {
                previous_workspace();
            }
            return false;
        case WORK_NW:
            if (record->event.pressed) {
                create_workspace();
            }
            return false;
        case WORK_CL:
            if (record->event.pressed) {
                remove_workspace();
            }
            return false;
        case WORK_SH:
            if (record->event.pressed) {
                show_workspaces();
            }
            return false;
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

#endif
