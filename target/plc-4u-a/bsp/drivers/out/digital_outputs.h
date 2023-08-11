#ifndef __DIGITAL_OUTPUTS_H
#define __DIGITAL_OUTPUTS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


// NO-OP: lack of I/O on mega328p

static inline void digital_output__0__set(bool value) {
}

static inline void digital_output__1__set(bool value) {
}

static inline void digital_output__2__set(bool value) {
}

static inline void digital_output__3__set(bool value) {
}

static inline void digital_output__4__set(bool value) {
}

static inline void digital_output__5__set(bool value) {
}

static inline void digital_output__6__set(bool value) {
}

static inline void digital_output__7__set(bool value) {
}

static inline void digital_output__8__set(bool value) {
}

static inline void digital_output__9__set(bool value) {
}

static inline void digital_output__a__set(bool value) {
}

static inline void digital_output__b__set(bool value) {
}

static inline void digital_output__c__set(bool value) {
}

static inline void digital_output__d__set(bool value) {
}

static inline void digital_output__e__set(bool value) {
}

static inline void digital_output__f__set(bool value) {
}


static inline void digital_outputs__init(void) {
    // Initial setting for all outputs is 0: not active
    digital_output__0__set(false);
    digital_output__1__set(false);
    digital_output__2__set(false);
    digital_output__3__set(false);
    digital_output__4__set(false);
    digital_output__5__set(false);
    digital_output__6__set(false);
    digital_output__7__set(false);
    digital_output__8__set(false);
    digital_output__9__set(false);
    digital_output__a__set(false);
    digital_output__b__set(false);
    digital_output__c__set(false);
    digital_output__d__set(false);
    digital_output__e__set(false);
    digital_output__f__set(false);
}


#endif
