#include "device.h"
#include <avr/io.h>

#include "device.h"

#include "usart.h"
#include "usart_rx.h"

#include "server.h"
#include "router.h"

#include "cpu/avr/asm.h"


inline void usart_rx_thread__process_packet(void) {
    register uint8_t *packet	asm("r28") = usart_rx_buffer;

    usart_rx_thread__w_ptr   = usart_rx_buffer;

    // If host=0:0 it is a query from host.
    if (!(*(packet+3))) {
        server__process_packet();
    }
    else {
        router__process_packet();
    }

    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    USART_TO_YPLUS();

    DEC(usart_rx_thread__remaining);
    IF_ZERO(usart_rx_thread__process_packet());
    RETI();    
}
