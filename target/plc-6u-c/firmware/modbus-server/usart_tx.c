// =============================================================================
// USART transmitter
// =============================================================================

#include "buffer.h"
#include "delay_timer.h"
#include "usart_tx.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"


ISR(usart0__tx__data_register_empty__interrupt__VECTOR) {
}

ISR(usart0__tx__complete__interrupt__VECTOR) {
}
