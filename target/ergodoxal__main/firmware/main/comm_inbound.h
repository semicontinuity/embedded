#ifndef COMM_INBOUND_H
#define COMM_INBOUND_H

#include <stdbool.h>

void comm_inbound__start(void);

void comm_inbound__thread__start(void);

bool comm_inbound__thread__is_runnable(void);

void comm_inbound__thread__run(void);

#endif
