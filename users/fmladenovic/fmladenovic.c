#include "fmladenovic.h"
#include "keychron_common.h"

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

