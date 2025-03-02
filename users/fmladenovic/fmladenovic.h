#pragma once

#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

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
    MAC_AWF,
    SPACE4,
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

enum tap_dances { // custom tap dance keys
    CAPS_LYRS,
};

td_state_t cur_dance(tap_dance_state_t *state);

void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

// ----------------------- Leader ------------------------

void leader_start_user(void);
void leader_end_user(void);

#endif
