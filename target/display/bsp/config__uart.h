#define USART_BAUD_RATE (9600UL)


// Defines for buffered-uart-receiver.c
// ------------------------------------

#define USART0__IN__BUFFER__SIZE (256)

// This macro is called every time a character has been placed to the buffer
// The index may have reached the top of the buffer
// If the index is at the top of the buffer, it must be reset to point to the
// beginning of the buffer
//
// In this implementation, USART buffer size is 256,
// so we just retain lower byte of index.
#define usart0__in__buffer__roll(index) do { index &= 0xFF; } while(0)
