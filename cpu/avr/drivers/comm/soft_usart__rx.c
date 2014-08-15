// =============================================================================
// Software USART driver, receiver module.
//
// The overall state of RX module is determined by the combination of
// bit soft_usart__rx__in_data_bits and soft_usart__rx__in_stop_bit:
//
// soft_usart__rx__in_data_bits == 0 and soft_usart__rx__in_stop_bit == 0:
//   receiving start bit
// soft_usart__rx__in_data_bits == 1:
//   receiving data bits
// soft_usart__rx__in_data_bits == 0 and soft_usart__rx__in_stop_bit == 1:
//   receiving stop bit

// In even more optimized version,
// current state can be derived from timer's state
// =============================================================================

#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/comm/soft_usart__rx.h"
#include "cpu/avr/drivers/comm/soft_usart__timer.h"


#ifdef SOFT_USART__RX__DATA__REG
register uint8_t soft_usart__rx__data asm(QUOTE(SOFT_USART__RX__DATA__REG));
#else
volatile uint8_t soft_usart__rx__data;
#endif

#ifdef SOFT_USART__RX__INDEX__REG
register  int8_t soft_usart__rx__index asm(QUOTE(SOFT_USART__RX__INDEX__REG));
#else
volatile  int8_t soft_usart__rx__index;
#endif


/**
 * Invoked periodically by the associated timer (if it is started)
 * with the delay, equal to 1 bit time, in the middle of start bit, every data bit, and stop bit.
 */
void soft_usart__rx__run(void) {
    if (soft_usart__rx__in_data_bits__get()) {
        if (--soft_usart__rx__index > 0) {
            soft_usart__rx__data >>= 1;
            uint8_t pin_data = PIN_REG(SOFT_USART__RX__PORT);
            COPY_BIT(pin_data, SOFT_USART__RX__PIN, soft_usart__rx__data, 7);
        }
        else {
            // for the next invocation (in stop bit)
            soft_usart__rx__in_data_bits__set(0); 
            soft_usart__rx__in_stop_bit__set(1);
        }
    }
    else {
        if (soft_usart__rx__in_stop_bit__get()) {
            // in stop bit
            soft_usart__timer__signal_stop_bit_middle();
            soft_usart__rx__in_stop_bit__set(0); // for the next invocation (start bit)
            soft_usart__rx__on_frame_end(); // not exacty - 1/2 of stop bit is still remaining.
            if (IS_1(SOFT_USART__RX)) {
                soft_usart__rx__on_character_received(soft_usart__rx__data);
            }
            else {
                soft_usart__rx__on_frame_error();
            }
        }
        else {
            // in start bit
            soft_usart__timer__signal_start_bit_middle();
            soft_usart__rx__in_data_bits__set(1); // for the next invocation (data bit 0)            
        }
    }
}


/** Invoked when the start of character is detected */
void soft_usart__rx__signal_character_start(void) {
    soft_usart__rx__on_frame_start();
    soft_usart__timer__signal_start_bit_begin();
}
