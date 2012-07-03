#include "device.h"
#include <avr/io.h>

#include "device.h"

#include "usart.h"
#include "usart_rx.h"
#include "route.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/bitops.h"


USART_RX_THREAD_INTERRUPT {

    USART_TO_YPLUS();

    __asm__ (
        "dec    %0			\n\t"
        "brne   usart_rx_reti		\n\t"	// If not all characters received, goto
        :: "r"(usart_rx_thread__remaining)
    );

    route();

    // Restore the original state to receive the next packet.
    usart_rx_thread__init();

    __asm__ (
        "usart_rx_reti:	reti		\n\t"
    );
}
