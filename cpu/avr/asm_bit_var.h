#ifndef __CPU__AVR__ASM_BIT_VAR_H
#define __CPU__AVR__ASM_BIT_VAR_H

#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>
#include <util/bitops.h>
#include <stdbool.h>
#include <stdint.h>

// draft
#define IF_1(name, code) do {                                                                           \
    name##__skip_next_instruction_if_1();                                                               \
    __asm__ __volatile__("rjmp L_" QUOTE(__LINE__));                                                    \
    code                                                                                                \
    __asm__ __volatile__("L_" QUOTE(__LINE__) ":");                                                     \
} while(0)

// draft
#define IF_0(name, code) do {                                                                           \
    name##__skip_next_instruction_if_0();                                                               \
    __asm__ __volatile__("rjmp L_" QUOTE(__LINE__));                                                    \
    do {code;} while (0);                                                                               \
    __asm__ __volatile__("L_" QUOTE(__LINE__) ":");                                                     \
} while(0)

// draft
#define DEFINE_HIGH_REGISTER_BITVAR(name, r, bit)                                                       \
	inline void name##__skip_next_instruction_if_1(void)	{                                           \
        __asm__ __volatile__ ("sbrs r" QUOTE(26) ", %0" :: "I"((bit)));                                 \
	}                                                                                                   \
	inline void name##__skip_next_instruction_if_0(void)	{                                           \
        __asm__ __volatile__ ("sbrc r" QUOTE(26) ", %0" :: "I"((bit)));                                 \
	}                                                                                                   \
	inline void name##__set_0(void)	{                                                                   \
        __asm__ __volatile__ ("andi r" QUOTE(r) ", %0" :: "M"((1U << (bit))));                          \
	}                                                                                                   \
	inline void name##__set_1(void)	{                                                                   \
        __asm__ __volatile__ ("ori r" QUOTE(r) ", %0" :: "M"( (1U << (bit))));                          \
	}                                                                                                   \
	inline void name##__set(char v)	{                                                                   \
	    if ((v))                                                                                        \
	        name##__set_1();                                                                            \
	    else                                                                                            \
	        name##__set_0();                                                                            \
	}                                                                                                   \
	inline void name##__set_from_bit_opt(const unsigned char v, const unsigned char v_bit)	{           \
	    name##__set_0();                                                                                \
	    if ((v & (1U << (v_bit))))                                                                      \
	        name##__set_1();                                                                            \
	}



#define DEFINE_REG_BITVAR(name, host, bit)                                                              \
    DEFINE_BITVAR(name, host, bit)                                                                      \
    inline unsigned char name##__if_set_const_a_else_const_b(uint8_t a, uint8_t b) {                    \
	    return IF_BIT_SET_CONST_A_ELSE_CONST_B(host, bit, a, b);                                        \
	}


#endif