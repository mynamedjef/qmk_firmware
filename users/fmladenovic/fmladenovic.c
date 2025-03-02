#include "fmladenovic.h"
#include "keychron_common.h"

// ---------------------- Tap Dance ----------------------

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LYRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// ----------------------- Leader ------------------------

void leader_start_user(void) {
    // do something when the leader key is pressed
}

void leader_end_user(void) {
    // tables (prefix ';')
    if (leader_sequence_three_keys(KC_SCLN, KC_M, KC_S)) { // <leader>;ms -> managed_servers
        SEND_STRING("managed_servers");
    } else if (leader_sequence_three_keys(KC_SCLN, KC_M, KC_D)) { // <leader>;md -> managed_databases
        SEND_STRING("managed_databases");
    } else if (leader_sequence_four_keys(KC_SCLN, KC_M, KC_R, KC_R)) { // <leader>;mrr -> managed_restore_requests
        SEND_STRING("managed_restore_requests");
    } // fields
    else if (leader_sequence_three_keys(KC_M, KC_S, KC_N)) { // <leader>msn -> managed_server_name
        SEND_STRING("managed_server_name");
    } else if (leader_sequence_three_keys(KC_M, KC_S, KC_I)) { // <leader>msi -> managed_server_id
        SEND_STRING("managed_server_id");
    } else if (leader_sequence_three_keys(KC_M, KC_D, KC_N)) { // <leader>mdn -> managed_database_name
        SEND_STRING("managed_database_name");
    } else if (leader_sequence_three_keys(KC_M, KC_D, KC_I)) { // <leader>mdi -> managed_database_id
        SEND_STRING("managed_database_id");
    } else if (leader_sequence_three_keys(KC_T, KC_R, KC_N)) { // <leader>trn -> private_cluster_tenant_ring_name
        SEND_STRING("private_cluster_tenant_ring_name");
    } else if (leader_sequence_three_keys(KC_R, KC_E, KC_S)) { // <leader>res -> restore_id
        SEND_STRING("restore_id");
    } else if (leader_sequence_three_keys(KC_R, KC_E, KC_Q)) { // <leader>req -> request_id
        SEND_STRING("request_id");
    } else if (leader_sequence_three_keys(KC_R, KC_R, KC_I)) { // <leader>rri -> restore_request_id
        SEND_STRING("restore_request_id");
    } else if (leader_sequence_four_keys(KC_T, KC_M, KC_S, KC_N)) { // <leader>tmsn -> target_managed_server_name
        SEND_STRING("target_managed_server_name");
    } else if (leader_sequence_four_keys(KC_T, KC_M, KC_S, KC_I)) { // <leader>tmsi -> target_managed_server_id
        SEND_STRING("target_managed_server_id");
    } else if (leader_sequence_four_keys(KC_T, KC_M, KC_D, KC_N)) { // <leader>tmdn -> target_managed_database_name
        SEND_STRING("target_managed_database_name");
    } else if (leader_sequence_four_keys(KC_T, KC_M, KC_D, KC_I)) { // <leader>tmdi -> target_managed_database_id
        SEND_STRING("target_managed_database_id");
    } // misc (prefix ',')
    else if (leader_sequence_three_keys(KC_COMM, KC_N, KC_A)) { // <leader>,na -> [NonActionable]
        SEND_STRING("[NonActionable]");
    } else if (leader_sequence_three_keys(KC_COMM, KC_M, KC_S)) { // <leader>,ms -> "Mitigation steps provided below"
        SEND_STRING("Mitigation steps provided below");
    }
}

// ----------------------- Key Maps ----------------------

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKTEST:
            if (record->event.pressed) {
                SEND_STRING_DELAY("SELECT * FROM managed_servers where name = ''" SS_TAP(X_LEFT), 10);
            } else {
                // when keycode QMKTEST is released
            }
            return true;

        case MAC_AWF:
            const char *text =
                "SELECT * INTO #tmp FROM active_workflows\n"
                "SELECT workflow_position.ToString() AS workflow_pos, * FROM #tmp \n"
                "WHERE request_id = '" SS_LCTL("v") "'\n"
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

    return process_record_keymap(keycode, record);
}

// ----------------- Tap Dance Functions -----------------

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

