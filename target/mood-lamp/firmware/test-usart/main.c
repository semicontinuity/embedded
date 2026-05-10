#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


uint8_t  comm_service__data[16];
uint16_t comm_service__data_length;

inline void comm_service__init(void) {
    usart0__rate__set(USART0__BAUD_RATE);
    usart0__rx__enabled__set(1);
}

inline void comm_service__run(void) {
    usart0__in__read();
    OUT_1(LED_R);

    usart0__in__read();
    OUT_1(LED_G);

    usart0__in__read();
    OUT_1(LED_B);
}


int main(void) {
    comm_service__init();
    USE_AS_OUTPUT(LED_R);
    USE_AS_OUTPUT(LED_G);
    USE_AS_OUTPUT(LED_B);

    for(;;) {
        comm_service__run();
    }
    return 0;
}
