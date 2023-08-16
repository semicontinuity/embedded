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

bool discrete_output__0__get(void) {
    return discrete_outputs__byte0 & _BV(0);
}


void discrete_output__1__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(1);
    else
        discrete_outputs__byte0 &= ~_BV(1);
}

bool discrete_output__1__get(void) {
    return discrete_outputs__byte0 & _BV(1);
}


void discrete_output__2__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(2);
    else
        discrete_outputs__byte0 &= ~_BV(2);
}

bool discrete_output__2__get(void) {
    return discrete_outputs__byte0 & _BV(2);
}


void discrete_output__3__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(3);
    else
        discrete_outputs__byte0 &= ~_BV(3);
}

bool discrete_output__3__get(void) {
    return discrete_outputs__byte0 & _BV(3);
}


void discrete_output__4__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(4);
    else
        discrete_outputs__byte0 &= ~_BV(4);
}

bool discrete_output__4__get(void) {
    return discrete_outputs__byte0 & _BV(4);
}


void discrete_output__5__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(5);
    else
        discrete_outputs__byte0 &= ~_BV(5);
}

bool discrete_output__5__get(void) {
    return discrete_outputs__byte0 & _BV(5);
}


void discrete_output__6__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(6);
    else
        discrete_outputs__byte0 &= ~_BV(6);
}

bool discrete_output__6__get(void) {
    return discrete_outputs__byte0 & _BV(6);
}


void discrete_output__7__set(bool value) {
    if (value)
        discrete_outputs__byte0 |= _BV(7);
    else
        discrete_outputs__byte0 &= ~_BV(7);
}

bool discrete_output__7__get(void) {
    return discrete_outputs__byte0 & _BV(7);
}


void discrete_output__8__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(0);
    else
        discrete_outputs__byte1 &= ~_BV(0);
}

bool discrete_output__8__get(void) {
    return discrete_outputs__byte1 & _BV(0);
}


void discrete_output__9__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(1);
    else
        discrete_outputs__byte1 &= ~_BV(1);
}

bool discrete_output__9__get(void) {
    return discrete_outputs__byte1 & _BV(1);
}


void discrete_output__a__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(2);
    else
        discrete_outputs__byte1 &= ~_BV(2);
}

bool discrete_output__a__get(void) {
    return discrete_outputs__byte1 & _BV(2);
}


void discrete_output__b__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(3);
    else
        discrete_outputs__byte1 &= ~_BV(3);
}

bool discrete_output__b__get(void) {
    return discrete_outputs__byte1 & _BV(3);
}


void discrete_output__c__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(4);
    else
        discrete_outputs__byte1 &= ~_BV(4);
}

bool discrete_output__c__get(void) {
    return discrete_outputs__byte1 & _BV(4);
}


void discrete_output__d__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(5);
    else
        discrete_outputs__byte1 &= ~_BV(5);
}

bool discrete_output__d__get(void) {
    return discrete_outputs__byte1 & _BV(5);
}


void discrete_output__e__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(6);
    else
        discrete_outputs__byte1 &= ~_BV(6);
}

bool discrete_output__e__get(void) {
    return discrete_outputs__byte1 & _BV(6);
}


void discrete_output__f__set(bool value) {
    if (value)
        discrete_outputs__byte1 |= _BV(7);
    else
        discrete_outputs__byte1 &= ~_BV(7);
}

bool discrete_output__f__get(void) {
    return discrete_outputs__byte1 & _BV(7);
}


void discrete_outputs__init(void) {
    discrete_outputs__byte0 = 0x00;
    discrete_outputs__byte1 = 0x00;
}


inline void discrete_outputs__set(uint8_t output, bool value) {
    if (output == 0x00) discrete_output__0__set(value);
    if (output == 0x01) discrete_output__1__set(value);
    if (output == 0x02) discrete_output__2__set(value);
    if (output == 0x03) discrete_output__3__set(value);
    if (output == 0x04) discrete_output__4__set(value);
    if (output == 0x05) discrete_output__5__set(value);
    if (output == 0x06) discrete_output__6__set(value);
    if (output == 0x07) discrete_output__7__set(value);
    if (output == 0x08) discrete_output__8__set(value);
    if (output == 0x09) discrete_output__9__set(value);
    if (output == 0x0A) discrete_output__a__set(value);
    if (output == 0x0B) discrete_output__b__set(value);
    if (output == 0x0C) discrete_output__c__set(value);
    if (output == 0x0D) discrete_output__d__set(value);
    if (output == 0x0E) discrete_output__e__set(value);
    if (output == 0x0F) discrete_output__f__set(value);
}


void discrete_outputs__run(void) {
    // uint8_t byte0 = discrete_outputs__byte0;
    // copy discrete_outputs 0..f to digital outputs 0..f
}
