#include "pwm.h"
#include "util/hex.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"

#include <avr/interrupt.h>


uint8_t  comm_service__data[16];
uint16_t comm_service__data_length;

inline void comm_service__init(void) {
    usart0__rate__set(USART__BAUD_RATE);
    usart0__rx__enabled__set(1);
}

inline void comm_service__read_line(void) {
    comm_service__data_length = 0;
    while (1) {
        register uint8_t c = usart0__in__read();

        if (c==13 || c==10) break;
        if (comm_service__data_length < sizeof(comm_service__data)) comm_service__data[comm_service__data_length++] = c;
    }
}

inline void comm_service__run(void) {
    while(1) {
        comm_service__read_line();
        if (comm_service__data_length == 6) {
            colors[0] = (uint8_t)byte__parse_hex(&comm_service__data[0]);
            colors[1] = (uint8_t)byte__parse_hex(&comm_service__data[2]);
            colors[2] = (uint8_t)byte__parse_hex(&comm_service__data[4]);
        }
    }
}


int main(void) {
    comm_service__init();
    pwm__init();
    pwm__start();

    sei();
    for(;;) {
        comm_service__run();
    }
    return 0;
}
