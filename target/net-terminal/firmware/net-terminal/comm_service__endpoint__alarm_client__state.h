#ifndef __COMM_SERVICE__ENDPOINT__AlARM_CLIENT__STATE_H
#define __COMM_SERVICE__ENDPOINT__AlARM_CLIENT__STATE_H

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include <stdint.h>


inline static void comm_service__endpoint__alarm_client__state__handle(void) {
    terminal_displayChar('S');
    terminal_displayChar('=');

    terminal_displayChar(kernel__frame.data[0] == 0 ? '0' : '1');

    terminal_displayChar('\n');
}


#endif