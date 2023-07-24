#ifndef DISCRETE_INPUTS_H
#define DISCRETE_INPUTS_H

#include <avr/io.h>


#ifndef discrete_inputs__byte0
extern uint8_t discrete_inputs__byte0;
#endif

#ifndef discrete_inputs__byte1
extern uint8_t discrete_inputs__byte1;
#endif

void discrete_inputs__init(void);

void discrete_inputs__debouncer__run(void);

#endif
