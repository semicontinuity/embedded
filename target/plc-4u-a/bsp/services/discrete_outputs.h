#ifndef __DISCRETE_OUTPUTS_H
#define __DISCRETE_OUTPUTS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


#ifndef discrete_outputs__byte0
extern uint8_t discrete_outputs__byte0;
#endif

#ifndef discrete_outputs__byte1
extern uint8_t discrete_outputs__byte1;
#endif


void discrete_outputs__init(void);
inline __attribute__((always_inline)) void discrete_outputs__set(uint8_t output, bool value);
inline __attribute__((always_inline)) bool discrete_outputs__get(uint8_t output);
void discrete_outputs__run(void);

#endif
