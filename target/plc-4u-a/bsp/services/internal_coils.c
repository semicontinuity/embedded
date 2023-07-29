#include "services/internal_coils.h"
#include <avr/io.h>


#ifndef internal_coils__byte0
uint8_t internal_coils__byte0;
#endif


void internal_coil__0__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(0);
    else
        internal_coils__byte0 &= ~_BV(0);
}

bool internal_coil__0__get(void) {
    return internal_coils__byte0 & _BV(0);
}


void internal_coil__1__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(1);
    else
        internal_coils__byte0 &= ~_BV(1);
}

bool internal_coil__1__get(void) {
    return internal_coils__byte0 & _BV(1);
}


void internal_coil__2__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(2);
    else
        internal_coils__byte0 &= ~_BV(2);
}

bool internal_coil__2__get(void) {
    return internal_coils__byte0 & _BV(2);
}


void internal_coil__3__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(3);
    else
        internal_coils__byte0 &= ~_BV(3);
}

bool internal_coil__3__get(void) {
    return internal_coils__byte0 & _BV(3);
}


void internal_coil__4__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(4);
    else
        internal_coils__byte0 &= ~_BV(4);
}

bool internal_coil__4__get(void) {
    return internal_coils__byte0 & _BV(4);
}


void internal_coil__5__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(5);
    else
        internal_coils__byte0 &= ~_BV(5);
}

bool internal_coil__5__get(void) {
    return internal_coils__byte0 & _BV(5);
}


void internal_coil__6__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(6);
    else
        internal_coils__byte0 &= ~_BV(6);
}

bool internal_coil__6__get(void) {
    return internal_coils__byte0 & _BV(6);
}


void internal_coil__7__set(bool value) {
    if (value)
        internal_coils__byte0 |= _BV(7);
    else
        internal_coils__byte0 &= ~_BV(7);
}

bool internal_coil__7__get(void) {
    return internal_coils__byte0 & _BV(7);
}
