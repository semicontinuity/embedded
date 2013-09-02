// =============================================================================
// USART receiver
// =============================================================================

#ifndef USART_RX_H
#define USART_RX_H

#include <stdbool.h>


void usart_rx__enable(void);

void usart_rx__disable(void);

void usart_rx__notify_t15_expired(void);

void usart_rx__notify_t35_expired(void);

bool usart_rx__is_frame_received(void);

/** Callback to be implemented */
void usart_rx__on_buffer_overflow(void);

/** Callback to be implemented */
void usart_rx__on_unexpected_data(void);

#endif