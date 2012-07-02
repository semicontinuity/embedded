#ifndef __GPIO_H
#define __GPIO_H

#include <avr/sfr_defs.h>
#include <avr/io.h>

#define set_bit_in_reg(reg,bit)      do {(reg) |= _BV(bit);} while(0)
#define clear_bit_in_reg(reg,bit)    do {(reg) &= ~_BV(bit);} while(0)

#define CONFIGURE_AS_OUTPUT(signal)  do {set_bit_in_reg (signal##_DIR, signal##_PIN);} while(0)
#define CONFIGURE_AS_INPUT(signal)   do {clear_bit_in_reg (signal##_DIR, signal##_PIN);} while(0)
#define DRIVE_LOW(signal)            do {clear_bit_in_reg (signal##_PORT, signal##_PIN);} while(0)
#define DRIVE_HIGH(signal)           do {set_bit_in_reg (signal##_PORT, signal##_PIN);} while(0)



// New style
#define QUOTE(x)                     #x
#define CONCAT(s1, s2)               s1##s2
#define DATA_DIR_REG(port)           CONCAT(DDR, port)
#define PORT_REG(port)               CONCAT(PORT, port)
#define PIN_REG(port)                CONCAT(PIN, port)


#define USE_AS_INPUT(signal)         do {clear_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define USE_AS_OUTPUT(signal)        do {set_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define ENABLE_PULLUP(signal)        do {set_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define TOGGLE(signal)               do {set_bit_in_reg (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)

#define OUT_0(signal)                do {clear_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define OUT_1(signal)                do {set_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)

#define PORT_VALUE(signal)           (PIN_REG(CONCAT(signal,__PORT)))
#define IS_0(signal)                 (bit_is_clear (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN))
#define IS_1(signal)                 (bit_is_set (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN))



#define STROBED_LOW(signal, op) do {\
    OUT_0(signal);\
    op;\
    OUT_1(signal);\
} while(0)

#endif // __GPIO_H