#include <stdint.h>
#include <stdbool.h>
#include "drivers/in/digital_inputs.h"

#include "cpu/avr/gpio.h"


static inline void digital_inputs__0__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__0);
}

inline bool digital_inputs__0__get(void) {
    return IS_1(DIGITAL_INPUTS__0);
}


static inline void digital_inputs__1__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__1);
}

inline bool digital_inputs__1__get(void) {
    return IS_1(DIGITAL_INPUTS__1);
}


static inline void digital_inputs__2__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__2);
}

inline bool digital_inputs__2__get(void) {
    return IS_1(DIGITAL_INPUTS__2);
}


static inline void digital_inputs__3__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__3);
}

inline bool digital_inputs__3__get(void) {
    return IS_1(DIGITAL_INPUTS__3);
}


static inline void digital_inputs__4__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__4);
}

inline bool digital_inputs__4__get(void) {
    return IS_1(DIGITAL_INPUTS__4);
}


static inline void digital_inputs__5__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__5);
}

inline bool digital_inputs__5__get(void) {
    return IS_1(DIGITAL_INPUTS__5);
}


static inline void digital_inputs__6__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__6);
}

inline bool digital_inputs__6__get(void) {
    return IS_1(DIGITAL_INPUTS__6);
}


static inline void digital_inputs__7__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__7);
}

inline bool digital_inputs__7__get(void) {
    return IS_1(DIGITAL_INPUTS__7);
}


static inline void digital_inputs__8__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__8);
}

inline bool digital_inputs__8__get(void) {
    return IS_1(DIGITAL_INPUTS__8);
}


static inline void digital_inputs__9__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__9);
}

inline bool digital_inputs__9__get(void) {
    return IS_1(DIGITAL_INPUTS__9);
}


static inline void digital_inputs__a__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__A);
}

inline bool digital_inputs__a__get(void) {
    return IS_1(DIGITAL_INPUTS__A);
}


static inline void digital_inputs__b__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__B);
}

inline bool digital_inputs__b__get(void) {
    return IS_1(DIGITAL_INPUTS__B);
}


static inline void digital_inputs__c__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__C);
}

inline bool digital_inputs__c__get(void) {
    return IS_1(DIGITAL_INPUTS__C);
}


static inline void digital_inputs__d__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__D);
}

inline bool digital_inputs__d__get(void) {
    return IS_1(DIGITAL_INPUTS__D);
}


static inline void digital_inputs__e__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__E);
}

inline bool digital_inputs__e__get(void) {
    return IS_1(DIGITAL_INPUTS__E);
}


static inline void digital_inputs__f__init(void) {
    ENABLE_PULLUP(DIGITAL_INPUTS__F);
}

inline bool digital_inputs__f__get(void) {
    return IS_1(DIGITAL_INPUTS__F);
}


void digital_inputs__init(void) {
    digital_inputs__0__init();
    digital_inputs__1__init();
    digital_inputs__2__init();
    digital_inputs__3__init();
    digital_inputs__4__init();
    digital_inputs__5__init();
    digital_inputs__6__init();
    digital_inputs__7__init();
    digital_inputs__8__init();
    digital_inputs__9__init();
    digital_inputs__a__init();
    digital_inputs__b__init();
    digital_inputs__c__init();
    digital_inputs__d__init();
    digital_inputs__e__init();
    digital_inputs__f__init();
}
