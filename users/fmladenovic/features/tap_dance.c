
#include "tap_dance.h"

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LYRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

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
            if (!leader_sequence_active()) {
                leader_start();
            }
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

