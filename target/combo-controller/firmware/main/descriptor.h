#ifndef __DESCRIPTOR_H
#define __DESCRIPTOR_H

#include <avr/pgmspace.h>
#include <stdint.h>

extern const uint8_t descriptor__value[] PROGMEM;
extern const uint8_t* const descriptor__address __attribute__((section(".descriptor__address")));

#endif