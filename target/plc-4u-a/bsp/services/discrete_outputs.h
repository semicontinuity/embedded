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


void discrete_output__0__set(bool value);
bool discrete_output__0__get(void);

void discrete_output__1__set(bool value);
bool discrete_output__1__get(void);

void discrete_output__2__set(bool value);
bool discrete_output__2__get(void);

void discrete_output__3__set(bool value);
bool discrete_output__3__get(void);

void discrete_output__4__set(bool value);
bool discrete_output__4__get(void);

void discrete_output__5__set(bool value);
bool discrete_output__5__get(void);

void discrete_output__6__set(bool value);
bool discrete_output__6__get(void);

void discrete_output__7__set(bool value);
bool discrete_output__7__get(void);

void discrete_output__8__set(bool value);
bool discrete_output__8__get(void);

void discrete_output__9__set(bool value);
bool discrete_output__9__get(void);

void discrete_output__a__set(bool value);
bool discrete_output__a__get(void);

void discrete_output__b__set(bool value);
bool discrete_output__b__get(void);

void discrete_output__c__set(bool value);
bool discrete_output__c__get(void);

void discrete_output__d__set(bool value);
bool discrete_output__d__get(void);

void discrete_output__e__set(bool value);
bool discrete_output__e__get(void);

void discrete_output__f__set(bool value);
bool discrete_output__f__get(void);

void discrete_outputs__init(void);
inline __attribute__((always_inline)) void discrete_outputs__set(uint8_t output, bool value);
inline __attribute__((always_inline)) bool discrete_outputs__get(uint8_t output);
void discrete_outputs__run(void);

#endif
