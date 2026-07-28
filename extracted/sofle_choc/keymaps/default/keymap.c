/* Copyright 2023 Brian Low 
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
 #include "eeprom.h"
 #include "quantum.h"
 #include "os_detection.h"

 enum layers {
     _COLEMAK_DH,
     _QWERTY,
     _SYMBOLS,
     _BRACKETS,
     _ARROWS,
     _NAV,
 };

 #define ARROW_O    LT(_ARROWS, KC_O)
 #define ARROW_SCLN LT(_ARROWS, KC_SCLN)
 #define NAV_Z      LT(_ARROWS, KC_Z)

 #define SYMBOLS_L  LT(_SYMBOLS,  KC_ESC)
 #define BRACKETS_L LT(_BRACKETS, KC_TAB)

bool process_detected_host_os_user(os_variant_t detected_os) {
    bool is_windows = (detected_os == OS_WINDOWS);
    keymap_config.swap_lctl_lgui = is_windows;
    keymap_config.swap_rctl_rgui = is_windows;
    return true;
}

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *   COLEMAK-DH
 *   .------------------------------------------.                    .------------------------------------------.
 *   | ESC   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |TO(QRT)|
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   | Tab   | Q/NAV|   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |   \   |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   | GUI   |   A  |   R  |   S  |   T  |   G  |                    |   M  |   N  |   E  |   I  |   O  |   '   |
 *   |-------+------+------+------+------+------+-------.    .-------+------+------+------+------+------+-------|
 *   | Shift |  Z   |   X  |   C  |   D  |   V  |  Mute |    | Play  |   K  |   H  |   ,  |   .  |   /  | Shift |
 *   '--------------+------+------+------+------+-------|    |-------+------+------+------+------+--------------'
 *                         | LCTL | LALT |  SPC |  SYM  |    |  ENT  | Bspc | BKTS | Del  |
 *                        '-----------------------------'    '----------------------------'
 */
 [_COLEMAK_DH] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(_QWERTY),
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
     KC_LGUI, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    ARROW_O, KC_QUOT,
     KC_LSFT, NAV_Z,   KC_X,    KC_C,    KC_D,    KC_V,    KC_MUTE,   KC_MPLY,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                              KC_LCTL, KC_LALT, KC_SPC,  SYMBOLS_L,   KC_ENT,   KC_BSPC, BRACKETS_L, KC_DEL
 ),

/*
 *   QWERTY
 *   .------------------------------------------.                    .------------------------------------------.
 *   | ESC   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |TO(CLM)|
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   | Tab   | Q/NAV|   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \   |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   | GUI   |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |   '   |
 *   |-------+------+------+------+------+------+-------.    .-------+------+------+------+------+------+-------|
 *   | Shift |  Z   |   X  |   C  |   V  |   B  |  Mute |    | Play  |   N  |   M  |   ,  |   .  |   /  | Shift |
 *   '--------------+------+------+------+------+-------|    |-------+------+------+------+------+--------------'
 *                         | LCTL | LALT |  SPC |  SYM  |    |  ENT  | Bspc | BKTS | Del  |
 *                         '----------------------------'    '----------------------------'
 */
 [_QWERTY] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(_COLEMAK_DH),
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
     KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    ARROW_SCLN, KC_QUOT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                       KC_LCTL, KC_LALT, KC_SPC,  SYMBOLS_L,         KC_ENT,   KC_BSPC, BRACKETS_L, KC_DEL
 ),
/*
 *   SYMBOLS
 *   .------------------------------------------.                    .------------------------------------------.
 *   |       |      |      |      |      |      |                    |      |      |      |      |      |       |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11  |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  F12  |
 *   |-------+------+------+------+------+------+-------.    .-------+------+------+------+------+------+-------|
 *   |       |   !  |   @  |   #  |   $  |   %  |       |    |       |   ^  |   &  |   *  |   (  |   )  |       |
 *   '--------------+------+------+------+------+-------|    |-------+------+------+------+------+--------------'
 *                  |      |      |      |      |       |    |       |      |      |      |
 *                  '-------------------------------'        '-------------------------'
 */
 [_SYMBOLS] = LAYOUT(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
     KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS,      KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),

/*
 *   BRACKETS - home row: [{(-_+=)}]`  top-right: ~
 *   .------------------------------------------.                    .------------------------------------------.
 *   |       |      |      |      |      |      |                    |      |      |      |      |      |   ~   |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |      |      |      |      |      |                    |      |      |      |      |      |       |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |   [  |   {  |   (  |   -  |   _  |                    |   +  |   =  |   )  |   }  |   ]  |   `   |
 *   |-------+------+------+------+------+------+-------.    .-------+------+------+------+------+------+-------|
 *   |       |      |      |      |      |      |       |    |       |      |      |      |      |      |       |
 *   '--------------+------+------+------+------+-------|    |-------+------+------+------+------+--------------'
 *                  |      |      |      |      |       |    |       |      |      |      |
 *                  '-----------------------------------'    '-----------------------------------'
 */
 [_BRACKETS] = LAYOUT(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS, KC_UNDS,                        KC_PLUS, KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),

/*
 *   ARROWS - inverted-T on right hand, page/home/end on left (middle=page, index=line)
 *   .------------------------------------------.                    .------------------------------------------.
 *   |       |      |      |      |      |      |                    |      |      |      |      |      |       |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |      |      | PgUp | Home |      |                    |      |      |  ↑   |      |      |       |
 *   |-------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 *   |       |      |      | PgDn | End  |      |                    |      |  ←   |  ↓   |  →   |      |       |
 *   |-------+------+------+------+------+------+-------.    .-------+------+------+------+------+------+-------|
 *   |       |      |      |      |      |      |       |    |       |      |      |      |      |      |       |
 *   '--------------+------+------+------+------+-------|    |-------+------+------+------+------+--------------'
 *                  |      |      |      |      |       |    |       |      |      |      |
 *                  '-----------------------------------'    '-----------------------------------'
 */
 [_ARROWS] = LAYOUT(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_HOME, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_END,  KC_TRNS,                        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),
};

 #if defined(ENCODER_MAP_ENABLE)
 const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
     [_COLEMAK_DH] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
     [_QWERTY]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
     [_SYMBOLS]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
     [_BRACKETS]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
     [_ARROWS]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
 };
 #endif
