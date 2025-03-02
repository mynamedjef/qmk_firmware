
#include "overrides.h"

const key_override_t override_gui_shift_h_to_move_window_left = ko_make_basic(MOD_MASK_GUI | MOD_MASK_SHIFT, KC_H, LSG(KC_LEFT)); // LSG() = left shift + gui mod
const key_override_t override_gui_shift_l_to_move_window_right = ko_make_basic(MOD_MASK_GUI | MOD_MASK_SHIFT, KC_L, LSG(KC_RGHT));

// Current documentation doesn't work, trying out older guide: https://github.com/qmk/qmk_firmware/blob/eee0384167b965c60120e1222bc24c0b40cadac4/docs/feature_key_overrides.md
const key_override_t *key_overrides[] = {
    // override 'ctrl+shift+alt+x = y' must be listed before 'ctrl+shift+x = z' because the former is a superset of the latter. In other case, ctrl+shift+alt+x would be mapped to alt+z.
    [GUI_SHIFT_H] = &override_gui_shift_h_to_move_window_left,
    [GUI_SHIFT_L] = &override_gui_shift_l_to_move_window_right,
};

