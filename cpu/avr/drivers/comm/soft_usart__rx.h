// =============================================================================
// Software USART driver, receiver module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H


/**
 * Invoked periodically by the associated timer (if it is started)
 * with the delay, equal to 1 bit time, in the middle of start bit, every data bit, and stop bit.
 */
void soft_usart__rx__run(void);

/** Invoked when the start of character is detected */
void soft_usart__rx__signal_character_start(void);


// Callbacks to be implemented
// -----------------------------------------------------------------------------

/** Invoked when start of frame is detected */
void soft_usart__rx__on_frame_end(void);

/** Invoked when end of frame is detected */
void soft_usart__rx__on_frame_end(void);

#endif
