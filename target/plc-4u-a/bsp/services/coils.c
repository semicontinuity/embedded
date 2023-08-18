#include "services/coils.h"
#include <avr/io.h>


#ifndef coils__byte0
uint8_t coils__byte0;
#endif

#ifndef coils__byte1
uint8_t coils__byte1;
#endif

#ifndef coils__byte2
uint8_t coils__byte2;
#endif

#ifndef coils__byte3
uint8_t coils__byte3;
#endif

#ifndef coils__byte4
uint8_t coils__byte4;
#endif


inline void coils__byte0__set(uint8_t bit, bool value) {
    if (value)
        coils__byte0 |= _BV(bit);
    else
        coils__byte0 &= ~_BV(bit);
}

inline bool coils__byte0__get(uint8_t bit) {
    return coils__byte0 & _BV(bit);
}



inline void coils__byte1__set(uint8_t bit, bool value) {
    if (value)
        coils__byte1 |= _BV(bit);
    else
        coils__byte1 &= ~_BV(bit);
}

inline bool coils__byte1__get(uint8_t bit) {
    return coils__byte1 & _BV(bit);
}


inline void coils__byte2__set(uint8_t bit, bool value) {
    if (value)
        coils__byte2 |= _BV(bit);
    else
        coils__byte2 &= ~_BV(bit);
}

inline bool coils__byte2__get(uint8_t bit) {
    return coils__byte2 & _BV(bit);
}


inline void coils__byte3__set(uint8_t bit, bool value) {
    if (value)
        coils__byte3 |= _BV(bit);
    else
        coils__byte3 &= ~_BV(bit);
}

inline bool coils__byte3__get(uint8_t bit) {
    return coils__byte3 & _BV(bit);
}


inline void coils__byte4__set(uint8_t bit, bool value) {
    if (value)
        coils__byte4 |= _BV(bit);
    else
        coils__byte4 &= ~_BV(bit);
}

inline bool coils__byte4__get(uint8_t bit) {
    return coils__byte4 & _BV(bit);
}


inline bool __attribute__((always_inline)) coils__get(uint8_t coil) {
    if (coil < 0x08)      return coils__byte0__get(coil);
    else if (coil < 0x10) return coils__byte1__get(coil - 0x08);
    else if (coil < 0x18) return coils__byte2__get(coil - 0x10);
    else if (coil < 0x20) return coils__byte3__get(coil - 0x18);
    else if (coil < 0x28) return coils__byte4__get(coil - 0x20);
    return false;
}


inline __attribute__((always_inline)) void coils__set(uint8_t coil, bool value) {
    if (coil < 0x08)      return coils__byte0__set(coil, value);
    else if (coil < 0x10) return coils__byte1__set(coil - 0x08, value);
    else if (coil < 0x18) return coils__byte2__set(coil - 0x10, value);
    else if (coil < 0x20) return coils__byte3__set(coil - 0x18, value);
    else if (coil < 0x28) return coils__byte4__set(coil - 0x20, value);
}


void coils__init(void) {
    coils__byte0 = 0x00;
    coils__byte1 = 0x00;
    coils__byte2 = 0x00;
    coils__byte3 = 0x00;
    coils__byte4 = 0x00;
    // Need to init Failure bits
}
