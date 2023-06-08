/* Do as you please
 * - pvillano
 */

#include QMK_KEYBOARD_H
#include "muse.h"

  enum preonic_layers {
    _QWERTY,
    _GAME,
    _ALT,
    _FUN,
  };

  const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------------------------------.
   * |  Esc   |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |   `    |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |   \    |
   * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
   * |  Tab   |    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |    ;   |   "    |
   * |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
   * |  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   | Enter  |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |  Ctrl  |  GUI   |  Alt   |  Func  |AltLayer|  Space |    _   |AltLayer|  Left  |  Down  |   Up   | Right  |
   * `-----------------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_preonic_grid(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
      KC_LCTL, KC_LGUI, KC_LALT, MO(_FUN),MO(_ALT),KC_SPC,  KC_UNDS, MO(_ALT),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /* Game
   * ,-----------------------------------------------------------------------------------------------------------.
   * |        |        |        |        |        |        |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |  NOOP  |        |        |        |        |  ALT   |        |        |        |        |        |
   * `-----------------------------------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT_preonic_grid(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, XXXXXXX, _______, _______, _______, _______, KC_LALT, _______, _______, _______, _______, _______
  ),

  /* Alt
   * ,-----------------------------------------------------------------------------------------------------------.
   * |        |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |Keypad 7|Keypad 8|Keypad 9|        |        |        |    -   |    +   |    {   |    }   |        |
   * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
   * |        |Keypad 4|Keypad 5|Keypad 6|        |        |        |    -   |    =   |    [   |    ]   |        |
   * |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
   * |        |Keypad 1|Keypad 2|Keypad 3|        |        |        |        |        |    <   |    >   |        |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |Keypad 0|Keypad 0|        |        |        |        |        |        |        |        |        |
   * `-----------------------------------------------------------------------------------------------------------'
   */
  [_ALT] = LAYOUT_preonic_grid(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
      _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
      _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______, _______, KC_LT,   KC_GT,   _______,
      _______, KC_P0,   KC_P0,   _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* Function
   * ,-----------------------------------------------------------------------------------------------------------.
   * |        |   F1   |   F2   |   F3   |   F4   |        |        |        |        |        |        |  Del   |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |   F5   |   F6   |   F7   |   F8   |        |        |        |        |        |program |        |
   * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
   * |        |   F9   |   F10  |   F11  |   F12  |  Game  |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |Num Lock|  Music |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |        |        |        |        |        |        |
   * `-----------------------------------------------------------------------------------------------------------'
   */
  [_FUN] = LAYOUT_preonic_grid(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, KC_DEL,
      _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, QK_BOOT, _______,
      _______, KC_F9,   KC_F10,  KC_F11,  KC_F12, TG(_GAME),_______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_NUM,  MU_TOGG, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
  };


  bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
      case MO(_FUN):
      case MO(_ALT):
      case KC_SPC:
      case KC_UNDS:
        return false;
      default:
        return true;
    }
  }
