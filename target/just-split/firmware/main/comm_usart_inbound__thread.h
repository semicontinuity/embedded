#ifndef COMM_USART_INBOUND__THREAD_H
#define COMM_USART_INBOUND__THREAD_H

#include <stdbool.h>

void comm_usart_inbound__thread__start(void);

bool comm_usart_inbound__thread__is_runnable(void);

void comm_usart_inbound__thread__run(void);

#endif
