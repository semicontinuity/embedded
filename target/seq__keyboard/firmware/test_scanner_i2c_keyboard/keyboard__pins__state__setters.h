#ifndef KEYBOARD__PINS__STATE__SETTERS_H
#define KEYBOARD__PINS__STATE__SETTERS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
void keyboard__pins__port_a__state__set(const uint8_t state);
#endif

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
void keyboard__pins__port_a__state__set(const uint8_t state);
#endif

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
void keyboard__pins__port_a__state__set(const uint8_t state);
#endif

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
void keyboard__pins__port_a__state__set(const uint8_t state);
#endif


#endif
