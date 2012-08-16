// Buffered UART receiver.
// Intended for cases when characters are received by UART faster than they can be processed.

// Parameters
// ===================================================================================
// In configuration file, included from device.h, the following must be defined:
// 
// USART0__IN__BUFFER__SIZE
// ===================================================================================

#include "device.h"

#include <stdint.h>
#include <avr/interrupt.h>


// We have UART circular buffer because data can arrive faster than we can process it
uint8_t usart0__buffer[USART0__IN__BUFFER__SIZE];

// Pointer to the free area of a circular buffer.
// Newly arriving characters will be written to this 
volatile uint16_t usart0__buffer_w_ptr;
// Pointer to the first character to be delivered to the application
volatile uint16_t usart0__buffer_r_ptr;
// The number of characters in the buffer that were received and not yet processed.
// If it has reached UART_RECEIVER_CIRCULAR_BUFFER_SIZE, it means that buffer is full and we cannot
// buffer incoming characters anymore, so they will be discarded.
volatile uint16_t usart0__buffer_remaining;


/**
 * This function is called every time a character has been placed to the buffer
 * the index may have reached the top of the buffer
 * If the index is at the top of the buffer, it must be reset to point to the
 * beginning of the buffer.
 */
inline uint16_t usart0__in__buffer__roll(uint16_t index) {
#if USART0__IN__BUFFER__SIZE & (USART0__IN__BUFFER__SIZE - 1)
    return (index >= USART0__IN__BUFFER__SIZE) ? 0 : index;
#else
    return index & (USART0__IN__BUFFER__SIZE - 1);
#endif
}


/**
 * When a character is received, this ISR is called.
 * If there were o framing erro and the buffer is not full, put the character to the buffer.
 */

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__)
ISR(USART_RX_vect) {
    uint8_t c = UDR0;
    if (bit_is_clear(UCSR0A, FE0) && usart0__buffer_remaining < USART0__IN__BUFFER__SIZE) 
#elif defined(__AVR_ATmega8__)
ISR(USART_RXC_vect) {
    uint8_t c = UDR;
    if (bit_is_clear(UCSRA, FE) && usart0__buffer_remaining < USART0__IN__BUFFER__SIZE)
#else
    #error "Unsupported MCU"
#endif

    {
        usart0__buffer[usart0__buffer_w_ptr] = c;
        ++usart0__buffer_w_ptr;
        usart0__buffer_w_ptr = usart0__in__buffer__roll(usart0__buffer_w_ptr);
        ++usart0__buffer_remaining;
    }
}


/**
 * Receives a byte from UART.
 * Blocks if no data available.
 */
uint8_t usart__in__read(void)
{
    while (usart0__buffer_remaining == 0);

    uint8_t c = usart0__buffer[usart0__buffer_r_ptr++];
    usart0__buffer_r_ptr = usart0__in__buffer__roll(usart0__buffer_r_ptr);
    --usart0__buffer_remaining;
    return c;
}
