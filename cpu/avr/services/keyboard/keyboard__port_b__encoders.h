#ifndef KEYBOARD__PORT_B__ENCODERS_H
#define KEYBOARD__PORT_B__ENCODERS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

void __attribute__((weak)) keyboard__port_b__encoders__process(uint8_t state, uint8_t changes) {}

#endif

#endif
