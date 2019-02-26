// =============================================================================
// Software USART driver, receiver module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H

#include <stdint.h>

/**
 * Invoked periodically by the associated timer (if it is started)
 * with the delay, equal to 1 bit time, in the middle of start bit, every data bit, and stop bit.
 */
void soft_usart__rx__run(void);

/** Invoked when the start of character is detected */
void soft_usart__rx__signal_character_start(void);


// Injected functions
// -----------------------------------------------------------------------------

/** Injected function to initialize RX start bit detector */
void soft_usart__rx__init(void);

/** Injected function to start RX start bit detector */
void soft_usart__rx__start(void);

/** Injected function to stop RX start bit detector */
void soft_usart__rx__stop(void);

/** Invoked when start of frame is detected */
void soft_usart__rx__on_frame_end(void);

/** Invoked when end of frame is detected */
void soft_usart__rx__on_frame_end(void);

/** Invoked when a valid frame has been received */
void soft_usart__rx__on_character_received(uint8_t c);

/** Invoked when an invalid frame has been received */
void soft_usart__rx__on_frame_error(void);

#endif
