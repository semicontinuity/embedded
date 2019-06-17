#ifndef KEYBOARD__PORT_B__BUTTONS_H
#define KEYBOARD__PORT_B__BUTTONS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

void keyboard__port_b__buttons__process(uint8_t state, uint8_t changes);

#endif

#endif
