#include "device.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "device.h"
#include "usart_tx.h"
#include "usart.h"
#include "packet.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"



USART_TX_Q_THREAD_INTERRUPT {
    usart_tx_q_thread__enabled__set(0);

    // TODO: optimize
    // if queue is not empty, remove packet from tail and ask 'usart_tx_thread' to transmit it to UART
    if (/*(usart_tx_q__w_ptr__lo8 != usart_tx_q__r_ptr__lo8) | (!*/usart_tx_q__remaining != USART_TX_Q_LENGTH) {
        usart_tx_q__remaining++;

        // Point 'usart_tx_thread__r_ptr' to the tail of the 'usart_tx_q'
        // Higher 8 bits are not changed
        usart_tx_thread__r_ptr__lo8 = usart_tx_q__r_ptr__lo8;
        // Remove the packet at the tail tail by moving the tail pointer
        // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
        usart_tx_q__r_ptr__lo8 += PACKET_Q_STRIDE;

        usart_tx_thread__remaining = PACKET_LENGTH;
        
        // Spawn 'usart_tx_thread' and yield to it
        usart_tx_thread__enabled__set(1);
    }


/*
        debug_putc('+');
        debug_putc('=');
        print_byte_as_hex(usart_tx_q__remaining);

        debug_putc(13);
        debug_putc(10);


        debug_putc('R');
        debug_putc('=');
        print_byte_as_hex(usart_tx_q__r_ptr__lo8);

        debug_putc(13);
        debug_putc(10);



        debug_putc('W');
        debug_putc('=');
        print_byte_as_hex(usart_tx_q__w_ptr__lo8);

        debug_putc(13);
        debug_putc(10);
*/

    __asm__ (
        "reti		\n\t"
    );
}



USART_TX_THREAD_INTERRUPT {

    XPLUS_TO_USART();

    __asm__ __volatile__ (
        "dec    %[count]		\n\t"
        "brne   usart_tx_reti		\n\t"	// If count is still > 0, goto
        : [count] "+r"(usart_tx_thread__remaining)
    );

    usart_tx_q_thread__enabled__set(1);
    usart_tx_thread__enabled__set(0);

    __asm__ __volatile__ (
        "usart_tx_reti:	reti		\n\t"
    );
}
