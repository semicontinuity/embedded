#ifndef __UNUSED_H
#define __UNUSED_H

#include "cpu/avr/gpio.h"

static inline void unused__init(void) {
    USE_AS_OUTPUT(UNUSED1);
    USE_AS_OUTPUT(UNUSED2);
    USE_AS_OUTPUT(UNUSED3);
    USE_AS_OUTPUT(UNUSED4);
    USE_AS_OUTPUT(UNUSED5);
    USE_AS_OUTPUT(UNUSED6);
    USE_AS_OUTPUT(UNUSED7);
    USE_AS_OUTPUT(UNUSED8);
    USE_AS_OUTPUT(UNUSED9);
    USE_AS_OUTPUT(UNUSED10);
    USE_AS_OUTPUT(UNUSED11);
    USE_AS_OUTPUT(UNUSED12);
    USE_AS_OUTPUT(UNUSED13);
}

#endif