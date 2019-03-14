#ifndef COMM_H
#define COMM_H

#include <stdint.h>

extern uint8_t comm__data[16 * 3];
extern volatile uint8_t *comm__rx__ptr;


void comm__init(void);

void comm__start(void);

#endif
