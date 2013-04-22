#ifndef __COMM_SERVICE__ENDPOINT__TTY_H
#define __COMM_SERVICE__ENDPOINT__TTY_H

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include <stdint.h>


inline static void comm_service__endpoint__io__handle_tty(const uint8_t is_get) {
    if (is_get) {
    }
    else {
        // Handle PUT request
        uint8_t* data = kernel__frame.data;
        for (int8_t n = kernel__frame.header.dlc; n-- >= 0;) {
            terminal_displayChar(*data++);
        }
    }
}


#endif