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


#endif