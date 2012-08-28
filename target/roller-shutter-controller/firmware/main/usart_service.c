#include <avr/io.h>
#include <stdint.h>

#include "usart_service.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/asm.h"



inline static void usart_rx_thread__on_packet_transferred(void) {

    volatile register uint8_t *packet	USART_RX_THREAD__W_PTR__REG;
    LOAD_ADDRESS(packet, comm_service__buffer);


    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    STORE_TO_XPLUS(usart__in__peek());

    DEC(usart_rx_thread__size);
    IF_ZERO(usart_rx_thread__on_packet_transferred());
    RETI();    
}


void usart_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data) {
}
