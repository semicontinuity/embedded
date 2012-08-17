#include <avr/io.h>
#include <stdint.h>
#include "packet.h"

#include "usart.h"
#include "usart_rx.h"

#include "server.h"
#include "router.h"

#include "cpu/avr/asm.h"


uint8_t usart_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));


inline static void usart_rx_thread__on_packet_transferred(void) {

    volatile register uint8_t *packet	asm("r28");
    LOAD_ADDRESS(packet, usart_rx_buffer);

    // If host=0:0 it is a query from host.
    if (!(*(packet+3))) {
        server__process_packet();
    }
    else {
        router__put_packet_to_can_tx_q();
    }

    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    USART_TO_YPLUS();

    DEC(usart_rx_thread__size);
    IF_ZERO(usart_rx_thread__on_packet_transferred());
    RETI();    
}
