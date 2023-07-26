#include "services/discrete_outputs.h"
#include <stdbool.h>


#ifndef discrete_outputs__byte0
uint8_t discrete_outputs__byte0;
#endif

#ifndef discrete_outputs__byte1
uint8_t discrete_outputs__byte1;
#endif


void discrete_output__0__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(0);
    else
        discrete_outputs__byte0 &= ~_BV(0);
}

void discrete_output__1__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(1);
    else
        discrete_outputs__byte0 &= ~_BV(1);
}

void discrete_output__2__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(2);
    else
        discrete_outputs__byte0 &= ~_BV(2);
}

void discrete_output__3__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(3);
    else
        discrete_outputs__byte0 &= ~_BV(3);
}

void discrete_output__4__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(4);
    else
        discrete_outputs__byte0 &= ~_BV(4);
}

void discrete_output__5__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(5);
    else
        discrete_outputs__byte0 &= ~_BV(5);
}

void discrete_output__6__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(6);
    else
        discrete_outputs__byte0 &= ~_BV(6);
}

void discrete_output__7__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(7);
    else
        discrete_outputs__byte0 &= ~_BV(7);
}

void discrete_output__8__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(0);
    else
        discrete_outputs__byte1 &= ~_BV(0);
}

void discrete_output__9__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(1);
    else
        discrete_outputs__byte1 &= ~_BV(1);
}

void discrete_output__a__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(2);
    else
        discrete_outputs__byte1 &= ~_BV(2);
}

void discrete_output__b__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(3);
    else
        discrete_outputs__byte1 &= ~_BV(3);
}

void discrete_output__c__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(4);
    else
        discrete_outputs__byte1 &= ~_BV(4);
}

void discrete_output__d__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(5);
    else
        discrete_outputs__byte1 &= ~_BV(5);
}

void discrete_output__e__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(6);
    else
        discrete_outputs__byte1 &= ~_BV(6);
}

void discrete_output__f__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(7);
    else
        discrete_outputs__byte1 &= ~_BV(7);
}


void discrete_outputs__run(void) {
}
