#ifndef __COMM_SERVICE__ENDPOINT__AlARM_CLIENT__AUTH_H
#define __COMM_SERVICE__ENDPOINT__AlARM_CLIENT__AUTH_H

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include <stdint.h>


inline static void comm_service__endpoint__alarm_client__auth__handle(void) {
    terminal_displayChar('A');
    terminal_displayChar('=');

    uint8_t* data = kernel__frame.data;
    for (int8_t n = kernel__frame.header.dlc; --n >= 0;) {
        terminal_displayChar(*data++);
    }
    terminal_displayChar('\n');
}


#endif