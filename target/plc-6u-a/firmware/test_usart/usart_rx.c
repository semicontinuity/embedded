#include <avr/io.h>
#include <stdint.h>
#include "packet.h"

#include "usart.h"
#include "usart_rx.h"

#include "cpu/avr/asm.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


uint8_t usart_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));


inline static void usart_rx_thread__on_packet_transferred(void) {
    volatile register uint8_t *packet	asm("r28");
    LOAD_ADDRESS(packet, usart_rx_buffer);

    usart0__out__write(packet[0]);

    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    USART_TO_YPLUS();

    DEC(usart_rx_thread__size);
    IF_ZERO(usart_rx_thread__on_packet_transferred());
    RETI();    
}
