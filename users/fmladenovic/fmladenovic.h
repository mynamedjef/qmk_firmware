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

// ----------------------- Leader ------------------------

void leader_start_user(void);
void leader_end_user(void);

#endif
