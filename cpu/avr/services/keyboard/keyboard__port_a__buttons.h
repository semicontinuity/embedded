#ifndef KEYBOARD__PORT_A__BUTTONS_H
#define KEYBOARD__PORT_A__BUTTONS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

void keyboard__port_a__buttons__process(uint8_t state, uint8_t changes);

#endif

#endif
