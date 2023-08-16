#include "services/internal_coils.h"
#include <avr/io.h>


#ifndef internal_coils__byte0
uint8_t internal_coils__byte0;
#endif

#ifndef internal_coils__byte1
uint8_t internal_coils__byte1;
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


void internal_coil__8__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(0);
    else
        internal_coils__byte1 &= ~_BV(0);
}

bool internal_coil__8__get(void) {
    return internal_coils__byte1 & _BV(0);
}


void internal_coil__9__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(1);
    else
        internal_coils__byte1 &= ~_BV(1);
}

bool internal_coil__9__get(void) {
    return internal_coils__byte1 & _BV(1);
}


void internal_coil__a__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(2);
    else
        internal_coils__byte1 &= ~_BV(2);
}

bool internal_coil__a__get(void) {
    return internal_coils__byte1 & _BV(2);
}


void internal_coil__b__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(3);
    else
        internal_coils__byte1 &= ~_BV(3);
}

bool internal_coil__b__get(void) {
    return internal_coils__byte1 & _BV(3);
}


void internal_coil__c__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(4);
    else
        internal_coils__byte1 &= ~_BV(4);
}

bool internal_coil__c__get(void) {
    return internal_coils__byte1 & _BV(4);
}


void internal_coil__d__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(5);
    else
        internal_coils__byte1 &= ~_BV(5);
}

bool internal_coil__d__get(void) {
    return internal_coils__byte1 & _BV(5);
}


void internal_coil__e__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(6);
    else
        internal_coils__byte1 &= ~_BV(6);
}

bool internal_coil__e__get(void) {
    return internal_coils__byte1 & _BV(6);
}


void internal_coil__f__set(bool value) {
    if (value)
        internal_coils__byte1 |= _BV(7);
    else
        internal_coils__byte1 &= ~_BV(7);
}

bool internal_coil__f__get(void) {
    return internal_coils__byte1 & _BV(7);
}


inline bool __attribute__((always_inline)) internal_coils__get(uint8_t coil) {
    if (coil == 0x00) return internal_coil__0__get();
    if (coil == 0x01) return internal_coil__1__get();
    if (coil == 0x02) return internal_coil__2__get();
    if (coil == 0x03) return internal_coil__3__get();
    if (coil == 0x04) return internal_coil__4__get();
    if (coil == 0x05) return internal_coil__5__get();
    if (coil == 0x06) return internal_coil__6__get();
    if (coil == 0x07) return internal_coil__7__get();
    if (coil == 0x08) return internal_coil__8__get();
    if (coil == 0x09) return internal_coil__9__get();
    if (coil == 0x0A) return internal_coil__a__get();
    if (coil == 0x0B) return internal_coil__b__get();
    if (coil == 0x0C) return internal_coil__c__get();
    if (coil == 0x0D) return internal_coil__d__get();
    if (coil == 0x0E) return internal_coil__e__get();
    if (coil == 0x0F) return internal_coil__f__get();
    return false;
}


inline __attribute__((always_inline)) void internal_coils__set(uint8_t coil, bool value) {
    if (coil == 0x00) internal_coil__0__set(value);
    if (coil == 0x01) internal_coil__1__set(value);
    if (coil == 0x02) internal_coil__2__set(value);
    if (coil == 0x03) internal_coil__3__set(value);
    if (coil == 0x04) internal_coil__4__set(value);
    if (coil == 0x05) internal_coil__5__set(value);
    if (coil == 0x06) internal_coil__6__set(value);
    if (coil == 0x07) internal_coil__7__set(value);
    if (coil == 0x08) internal_coil__8__set(value);
    if (coil == 0x09) internal_coil__9__set(value);
    if (coil == 0x0A) internal_coil__a__set(value);
    if (coil == 0x0B) internal_coil__b__set(value);
    if (coil == 0x0C) internal_coil__c__set(value);
    if (coil == 0x0D) internal_coil__d__set(value);
    if (coil == 0x0E) internal_coil__e__set(value);
    if (coil == 0x0F) internal_coil__f__set(value);
}


void internal_coils__init(void) {
    internal_coils__byte0 = 0x00;
    internal_coils__byte1 = 0x00;
    // Need to init Failure bits
}
