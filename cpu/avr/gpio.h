#ifndef __GPIO_H
#define __GPIO_H

#include <avr/sfr_defs.h>
#include <avr/io.h>
#include "cpu/avr/macros.h"

#define set_bit_in_reg(reg,bit)      do {(reg) |= _BV(bit);} while(0)
#define clear_bit_in_reg(reg,bit)    do {(reg) &= ~_BV(bit);} while(0)

#define DECLARE_CLEAR_ONLY_BITVAR(name)         \
	inline void name##__clear(void);        \
	inline char name##__get(void);

#define DEFINE_CLEAR_ONLY_BITVAR(name, host, bit)                               \
	inline void name##__clear(void)	{ (host) &= ~(1 << (bit));}             \
	inline char name##__get(void)	{ return (host) & (1 << (bit)); }


#define SIGNAL_PORT(signal)          CONCAT(signal,__PORT)
#define SIGNAL_PIN(signal)           CONCAT(signal,__PIN)
#define SIGNAL_PORT_REG(port)        CONCAT(PORT, SIGNAL_PORT(port))

#define DATA_DIR_REG(port)           CONCAT(DDR, port)
#define PORT_REG(port)               CONCAT(PORT, port)
#define PIN_REG(port)                CONCAT(PIN, port)


#define OUT(port,value)              do {PORT_REG(CONCAT(port,__PORT)) = (value);} while(0)
#define IN(port)                     (PIN_REG(CONCAT(port,__PORT)))
#define USE_PORT_AS_INPUT(port)      do {DATA_DIR_REG(CONCAT(port,__PORT)) = 0x00;} while(0)
#define USE_PORT_AS_OUTPUT(port)     do {DATA_DIR_REG(CONCAT(port,__PORT)) = 0xFF;} while(0)
#define DISABLE_PULLUPS(port)        do {PORT_REG(CONCAT(port,__PORT)) = 0x00;} while(0)
#define ENABLE_PULLUPS(port)         do {PORT_REG(CONCAT(port,__PORT)) = 0xFF;} while(0)

#define USE_AS_INPUT(signal)         do {clear_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define USE_AS_OUTPUT(signal)        do {set_bit_in_reg (DATA_DIR_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define DISABLE_PULLUP(signal)       do {clear_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define ENABLE_PULLUP(signal)        do {set_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define TOGGLE(signal)               do {set_bit_in_reg (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)

#define SIGNAL_MASK(signal)          (_BV(signal##__PIN))
#define OUT_0_RAW(signal)            (PORT_REG(CONCAT(signal,__PORT)) &= ~SIGNAL_MASK(signal))
#define OUT_0(signal)                do {clear_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)
#define OUT_1_RAW(signal)            (PORT_REG(CONCAT(signal,__PORT)) |= SIGNAL_MASK(signal))
#define OUT_1(signal)                do {set_bit_in_reg (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN);} while(0)

#define PORT_VALUE(port)             IN(port)
#define IS_0(signal)                 (bit_is_clear (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN))
#define IS_OUT_0(signal)             (bit_is_clear (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN))
#define IS_1(signal)                 (bit_is_set (PIN_REG(CONCAT(signal,__PORT)), signal##__PIN))
#define IS_OUT_1(signal)             (bit_is_set (PORT_REG(CONCAT(signal,__PORT)), signal##__PIN))

#define DECLARE_OUT_SIGNAL(name) \
	void name##__set(char v);\
	char name##__get(void);

#define DEFINE_OUT_SIGNAL(name,signal) \
	void name##__set(char v)     { if ((v)) OUT_1(signal); else OUT_0(signal);}\
	char name##__get(void)       { return IS_1(signal); }


#endif // __GPIO_H