#ifndef __DEBUG_H
#define __DEBUG_H


#define debug__write(v) do {			\
    loop_until_bit_is_set(UCSR0A, UDRE0);	\
    __asm__ __volatile__(			\
        "sts 0x00C6, %0\n\t"			\
        :: "r"(v)				\
    );						\
} while(0)


#endif