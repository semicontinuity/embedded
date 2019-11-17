#ifndef KEYBOARD__PORT_D__ENCODERS_H
#define KEYBOARD__PORT_D__ENCODERS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

void keyboard__port_d__encoders__process(uint8_t state, uint8_t changes);

#endif

#endif
