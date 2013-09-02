// =============================================================================
// USART transmitter
// =============================================================================

#ifndef USART_TX_H
#define USART_TX_H

#include <stdbool.h>


void usart_tx__enable(void);


void usart_tx__disable(void);


/** Callback to be implemented */
void usart_tx__on_frame_sent(void);

#endif