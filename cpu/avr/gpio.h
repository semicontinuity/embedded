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
#ifndef QUOTE
#define QUOTE__(x)                   #x
#define QUOTE_(x)                    QUOTE__(x)
#define QUOTE(x)                     QUOTE_(x)
#endif

#ifndef CONCAT
#define CONCAT2(s1, s2)              s1##s2
#define CONCAT(s1, s2)               CONCAT2(s1, s2)
#endif

#define DATA_DIR_REG(port)           CONCAT(DDR, port)
#define PORT_REG(port)               CONCAT(PORT, port)
#define PIN_REG(port)                CONCAT(PIN, port)


#define OUT(port,value)              do {PORT_REG(CONCAT(port,__PORT)) = (value);} while(0)
#define IN(port)                     (PIN_REG(CONCAT(port,__PORT)))
#define USE_PORT_AS_INPUT(port)      do {DATA_DIR_REG(CONCAT(port,__PORT)) = 0x00;} while(0)
#define USE_PORT_AS_OUTPUT(port)     do {DATA_DIR_REG(CONCAT(port,__PORT)) = 0xFF;} while(0)
#define ENABLE_PULLUPS(port)         do {PORT_REG(CONCAT(port,__PORT)) = 0xFF;} while(0)

#define USE_AS_INPUT(signal)         do {clear_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define USE_AS_OUTPUT(signal)        do {set_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define ENABLE_PULLUP(signal)        do {set_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define TOGGLE(signal)               do {set_bit_in_reg (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)

#define SIGNAL_MASK(signal)          (_BV(signal##__PIN))
#define OUT_0_RAW(signal)            (PORT_REG(CONCAT(signal,__PORT)) &= ~SIGNAL_MASK(signal))
#define OUT_0(signal)                do {clear_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define OUT_1_RAW(signal)            (PORT_REG(CONCAT(signal,__PORT)) |= SIGNAL_MASK(signal))
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