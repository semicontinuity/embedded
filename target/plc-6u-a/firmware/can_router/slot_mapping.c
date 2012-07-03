#include <avr/pgmspace.h>
#include <avr/io.h>

// Entry format:
// (lo8(PORT address), MASK for SELECT signal).
// To get MASK for INT signal, multiply the mask for SELECT signal by 2.
unsigned char SUBNET_TO_PORT PROGMEM =
{
    0x00, 	0x00,	// Subnet 0 is reserved
    PORTC,	_BV(2),	// Subnet 1 maps to slot 0 (PC2)
};