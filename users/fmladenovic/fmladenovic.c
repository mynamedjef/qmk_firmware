
#include "quantum.h"
#include "keychron_common.h"

#include "definitions/macros.h"


// ----------------------- Key Maps ----------------------

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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

