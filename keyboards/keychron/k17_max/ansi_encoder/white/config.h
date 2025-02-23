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

#pragma once

#ifdef LED_MATRIX_ENABLE
/* LED Matrix driver configuration */
#    define LED_MATRIX_LED_COUNT 103
#    define DRIVER_COUNT 1
#    define DRIVER_CS_PINS \
        { B9 }

/* Scan phase of led driver set as MSKPHASE_8CHANNEL(defined as 0x03 in snled27351.h) */
#    define SNLED27351_PHASE_CHANNEL MSKPHASE_8CHANNEL
/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A }

/* Set to infinit, which is use in USB mode by default */
#    define LED_MATRIX_TIMEOUT LED_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#    define LED_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Turn off backlight on low brightness to save power */
#    define LED_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48

/* Indications */
#    define DIM_CAPS_LOCK
#    define CAPS_LOCK_INDEX 57
#    define LOW_BAT_IND_INDEX \
        { 94 }
#    define BT_HOST_LED_MATRIX_LIST \
        { 20, 21, 22 }
#    define P2P4G_HOST_LED_MATRIX_LIST \
        { 23 }
#    define BAT_LEVEL_LED_LIST \
        { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 }

#    define LED_MATRIX_KEYPRESSES
#endif
