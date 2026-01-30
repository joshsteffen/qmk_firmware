#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(85, RGB_RED);
        rgb_matrix_set_color(86, RGB_GREEN); // TODO: scroll lock
        rgb_matrix_set_color(87, RGB_BLUE);  // TODO: battery
    }
    return true;
}

#endif
