#ifndef KEYBOARD__PORT_C__ENCODERS_H
#define KEYBOARD__PORT_C__ENCODERS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

void keyboard__port_c__encoders__process(uint8_t state, uint8_t changes) __attribute__((weak));

#endif

#endif
