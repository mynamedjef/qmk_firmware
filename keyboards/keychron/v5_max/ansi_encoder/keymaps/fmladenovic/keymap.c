/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    MY_LAYER_0,
    MY_LAYER_1,
};

// ----------------------- Macros ------------------------

enum custom_keycodes {
    QMKTEST = SAFE_RANGE,
    TESTSEL,
    MAC_AWF,
    SPACE4,
};

// ----------------------- Combos ------------------------

enum combos {
    SPC_BSPC,
};

const uint16_t PROGMEM combo_spc_bspc_to_del[]   = {KC_SPC, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    [SPC_BSPC]  = COMBO(combo_spc_bspc_to_del, KC_DEL),
};

// -------------------- Key Overrides --------------------

const key_override_t override_gui_shift_h_to_move_window_left = ko_make_basic(MOD_MASK_GUI | MOD_MASK_SHIFT, KC_H, LSG(KC_LEFT)); // LSG() = left shift + gui mod
const key_override_t override_gui_shift_l_to_move_window_right = ko_make_basic(MOD_MASK_GUI | MOD_MASK_SHIFT, KC_L, LSG(KC_RGHT));

// Current documentation doesn't work, trying out older guide: https://github.com/qmk/qmk_firmware/blob/eee0384167b965c60120e1222bc24c0b40cadac4/docs/feature_key_overrides.md
const key_override_t **key_overrides = (const key_override_t *[]){
    // override 'ctrl+shift+alt+x = y' must be listed before 'ctrl+shift+x = z' because the former is a superset of the latter. In other case, ctrl+shift+alt+x would be mapped to alt+z.
    &override_gui_shift_h_to_move_window_left,
    &override_gui_shift_l_to_move_window_right,
    NULL
};

// ---------------------- Tap Dance ----------------------

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum tap_dances { // custom tap dance keys
    CAPS_LYRS,
};


td_state_t cur_dance(tap_dance_state_t *state);

void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

// associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LYRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// ----------------------- Key Maps ----------------------

const int LAYER0 = MO(MY_LAYER_0);
const int CLEFT = LCTL(KC_LEFT);
const int CRIGHT = LCTL(KC_RGHT);
const int TD_CAPS = TD(CAPS_LYRS);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [MAC_BASE] = LAYOUT_ansi_98(
        _______,             _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,   _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,   _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,   _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,
        _______,             _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,   _______,                               _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______               ),
    [MAC_FN] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [WIN_BASE] = LAYOUT_ansi_98(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,    KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,      KC_PPLS,
        TD_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  _______,  KC_P1,    KC_P2,    KC_P3,      KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  _______,  _______,  _______,  KC_P0,    KC_PDOT            ),
    [WIN_FN] = LAYOUT_ansi_98(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  KC_DEL,             _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        KC_CAPS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  MAC_AWF,  TESTSEL,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  QMKTEST,  _______            ),
    [MY_LAYER_0] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            KC_INS,   KC_PGUP,  KC_PGDN,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  KC_DEL,   _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,              _______,            _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                SPACE4,                                 _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [MY_LAYER_1] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  QK_BOOT,  QK_MAKE,  _______,  _______,  _______,  CLEFT,    KC_END,   KC_HOME,  CRIGHT,   _______,  _______,              _______,            _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
 };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]     = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]     = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [MY_LAYER_0] = {ENCODER_CCW_CW(KC_NO, KC_NO)}, // no-op
    [MY_LAYER_1] = {ENCODER_CCW_CW(KC_NO, KC_NO)}, // no-op
};
#endif // ENCODER_MAP_ENABLE

int selection = -1;
int last_selected = 0;
const char* options[] = {"source_managed_server_name", "target_managed_server_name", "source_managed_database_name", "target_managed_database_name", "request_id"};

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != TESTSEL) {
        selection = -1;
    }

    switch (keycode) {
        case QMKTEST:
            if (record->event.pressed) {
                SEND_STRING_DELAY("SELECT * FROM managed_servers where name = ''" SS_TAP(X_LEFT), 10);
            } else {
                // when keycode QMKTEST is released
            }
            return true;

        // selection test. pressing the key will cycle through the options. last selected option will be the first next time the key is pressed
        case TESTSEL:
            if (record->event.pressed) {
                if (selection == -1) {
                    selection = last_selected;

                    SEND_STRING(options[selection]);
                } else {
                    for (uint8_t i = 0; i < strlen(options[selection]); i++) {
                        SEND_STRING(SS_TAP(X_BSPC));
                    }

                    selection = (selection + 1) % (sizeof(options) / sizeof(options[0]));
                    SEND_STRING(options[selection]);

                    last_selected = selection;
                }
            } else {
                // when keycode TESTSEL is released
            }
            return true;

        case MAC_AWF:
            const char *text =
                "SELECT * INTO #tmp FROM active_workflows\n"
                "SELECT workflow_position.ToString() AS workflow_pos, * FROM #tmp \n"
                "WHERE request_id = ''\n"
                "ORDER BY request_id, workflow_position";

            if (record->event.pressed) {
                SEND_STRING_DELAY(text, 10);
            } else {

            }
            return true;

        case SPACE4:
            if (record->event.pressed) {
                SEND_STRING("    ");
            } else {
                // when keycode SPACE4 is released
            }
            return true;
    }
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

// determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// initialize tap structure
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// tap dance function
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(MY_LAYER_0);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_COMMA);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(MY_LAYER_1);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // if the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(MY_LAYER_0);
    } else if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(MY_LAYER_1);
    }
    ql_tap_state.state = TD_NONE;
}

