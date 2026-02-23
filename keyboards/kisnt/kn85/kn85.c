/* Copyright 2026 Josh Steffen (@joshsteffen)
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

#include "quantum.h"

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    switch (index) {
        case 1:
            // 2.4GHz mode
            break;
        case 2:
            // Bluetooth mode
            break;
        default:
            break;
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(85, RGB_WHITE);
    } else {
        rgb_matrix_set_color(85, RGB_OFF);
    }

    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(86, RGB_WHITE);
    } else {
        rgb_matrix_set_color(86, RGB_OFF);
    }

    rgb_matrix_set_color(87, RGB_OFF);

    return true;
}
#endif
