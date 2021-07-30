#ifndef KEYBOARD__PORT_H__BUTTONS_H
#define KEYBOARD__PORT_H__BUTTONS_H

#include <stdint.h>

#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1

void keyboard__port_h__buttons__process(uint8_t state, uint8_t changes);

#endif

#endif
