#include <avr/interrupt.h>
#include "comm_usart_inbound__thread.h"


ISR(WDT_vect, ISR_NAKED) {
    comm_usart_inbound__thread__reset();
}
