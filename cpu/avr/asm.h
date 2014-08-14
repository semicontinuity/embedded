#ifndef __CPU__AVR__ASM_H
#define __CPU__AVR__ASM_H

#include <stdint.h>

unsigned char __builtin_avr_insert_bits (unsigned long map, unsigned char bits, unsigned char val);

// macro to spare warnings about used registers in case when some interfering fixed registers are defined.
#define avr_insert_bits_map(b7,b6,b5,b4,b3,b2,b1,b0) (\
    (uint32_t)(\
    (((uint32_t)b7)<<(4*7)) |\
    (((uint32_t)b6)<<(4*6)) |\
    (((uint32_t)b5)<<(4*5)) |\
    (((uint32_t)b4)<<(4*4)) |\
    (((uint32_t)b3)<<(4*3)) |\
    (((uint32_t)b2)<<(4*2)) |\
    (((uint32_t)b1)<<(4*1)) |\
    (((uint32_t)b0)<<(4*0))\
    )\
)


#define FIX_POINTER(_ptr)               __asm__ __volatile__("" : "=b" (_ptr) : "0" (_ptr))
#define FIX_POINTER_XYZ(_ptr)           __asm__ __volatile__("" : "=e" (_ptr) : "0" (_ptr))
#define FIX_POINTER_X(_ptr)             __asm__ __volatile__("" : "=x" (_ptr) : "0" (_ptr))
#define FIX_POINTER_Y(_ptr)             __asm__ __volatile__("" : "=y" (_ptr) : "0" (_ptr))
#define FIX_POINTER_Z(_ptr)             __asm__ __volatile__("" : "=z" (_ptr) : "0" (_ptr))

#define POINTER_X(_ptr)                 __asm__ __volatile__("" : "=x" (_ptr) : "0" (_ptr))

// =============================================================================
// Macros for some of the instructions from the AVR instruction set.
// =============================================================================
#ifndef QUOTE
#define QUOTE__(x)                      #x
#define QUOTE_(x)                       QUOTE__(x)
#define QUOTE(x)                        QUOTE_(x)
#endif

#ifndef CONCAT
#define CONCAT2(s1, s2)                 s1##s2
#define CONCAT(s1, s2)                  CONCAT2(s1, s2)
#endif

#define MARKED_LABEL(prefix, mark)      #prefix "__" mark
#define TMP_LABEL(p)	                MARKED_LABEL(p, QUOTE(__LINE__))
#define MARK(label)		                do { __asm__ __volatile__( #label ":"); } while(0)
#define MARK0(label)                            do { __asm__ __volatile__( label ":"); } while(0)


#define COPY_BIT(src, srcbit, dst, dstbit)      do {    \
  asm volatile (                                        \
    "bst  %1, %2 \r\n"                                  \
    "bld  %0, %3 \r\n"                                  \
    : "+r" (dst)                                        \
    : "r" (src),                                        \
      "I" (srcbit),                                     \
      "I" (dstbit)                                      \
  );                                                    \
} while(0)


#define CONST_LO8(k)			\
(__extension__({                        \
    uint8_t __result;                   \
    __asm__ (		\
    "ldi %0, %1\n\t"			\
        : "=d"(__result)		\
        : "M"((uint8_t)((k) & 0xFF))	\
    );                                  \
    __result;                           \
}))


#define LOAD_CONST8(var, k)	do {	\
  __asm__ __volatile__ (		\
    "ldi %0, %1\n\t"			\
        : "=d"(var)			\
        : "M"(k)			\
  );					\
} while(0)


#define AND_CONST_LO8(var, k)	do {    \
  __asm__ __volatile__ (                \
    "andi %A0, %1\n\t"                  \
        : "=d"(var)                     \
        : "M"(k)                        \
  );                                    \
} while(0)


#define LOAD_CONST_LO8(var, k)	do {	\
  __asm__ __volatile__ (		\
    "ldi %A0, %1\n\t"			\
        : "=d"(var)			\
        : "M"((uint8_t)((k) & 0xFF))	\
  );					\
} while(0)


#define LOAD_CONST16(var, k)	do {	\
  __asm__ __volatile__ (		\
    "ldi %A0, %1\n\t"			\
    "ldi %B0, %2\n\t"			\
        : "=d"(var)			\
        : "M"((uint8_t)((k) & 0xFF)),	\
	  "M"((uint8_t)((k) >> 8))	\
  );					\
} while(0)


#define LOAD_ADDRESS(var, addr)	do {	\
  __asm__ __volatile__ (		\
    "ldi %A0, lo8(" #addr ")\n\t"	\
    "ldi %B0, hi8(" #addr ")\n\t"	\
        : "=d"(var)			\
  );					\
} while(0)


#define LOAD_ADDRESS_OFFSET(var, addr, off)	do {	\
  __asm__ __volatile__ (				\
    "ldi %A0, lo8(" #addr "+ " QUOTE(off) ")\n\t"       \
    "ldi %B0, hi8(" #addr "+ " QUOTE(off) ")\n\t"	\
        : "=d"(var)					\
  );							\
} while(0)


#define LOAD_ADDRESS_LO8(var, addr)	do {		\
  __asm__ __volatile__ (				\
    "ldi %0, lo8(" #addr ")\n\t"			\
        : "=d"(var)					\
  );							\
} while(0)


#define LOAD_ADDRESS_HI8(var, addr)	do {		\
  __asm__ __volatile__ (				\
    "ldi %0, hi8(" #addr ")\n\t"			\
        : "=d"(var)					\
  );							\
} while(0)


#define LOAD_ADDRESS_HI8_OF(var, addr)	do {		\
  __asm__ __volatile__ (				\
    "ldi %B0, hi8(" #addr ")\n\t"			\
        : "=d"(var)					\
  );							\
} while(0)


#define SET_LO8_OF(u16_dst, src)	do {	\
  __asm__ __volatile__ (			\
    "mov %A0, %A1	\n\t"			\
        : "=r"(u16_dst) : "r"(src)		\
  );						\
} while(0)



#define GOTO_IF_BIT_SET(r, b, l) do {	\
  __asm__ __volatile__ (		\
    "sbis %0, %1\n\t"			\
    "rjmp " #l "\n\t"			\
        :				\
        : "I"(_SFR_IO_ADDR(r)),		\
          "I"(b)			\
  );					\
} while(0)


#define COMPARE_LO8_SKIP_IF_EQUAL(v1, v2, code) do {\
  __asm__ __volatile__(                         \
    "cpse %A0, %A1\n\t"                         \
        :                                       \
        : "r"(v1),"r"(v2)                       \
  );					                        \
  do {code;} while(0);                          \
} while(0)


#define IF_LO8_EQUAL(v1, v2, code) do {         \
  __asm__ __volatile__(                         \
    "cpse %A0, %A1\n\t"                         \
    "rjmp L_" QUOTE(__LINE__) "\n\t"            \
        :                                       \
        : "r"(v1),"r"(v2)                       \
  );					                        \
  do {code;} while(0);                          \
  __asm__ __volatile__(                         \
    "L_" QUOTE(__LINE__) ":\n\t"::              \
  );\
} while(0)


#define IF_LO8_EQUAL_CLEAR_IO_BIT(v1, v2, addr, bit) do {\
  __asm__ __volatile__(                         \
    "cpse %A0, %A1\n\t"                         \
    "rjmp L_%=\n\t"                             \
    "cbi  %2, %3\n\t"                           \
    "L_%=:\n\t"                                 \
    :                                           \
    : "r"(v1),                                  \
      "r"(v2),                                  \
      "I"(_SFR_IO_ADDR(addr)),                  \
      "I"(bit)                                  \
  );\
} while(0)


// ----------------------------------------------
// Operations with X register
// ----------------------------------------------

#define LOAD_XPLUS(ptr)			        \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, x+\n\t"                             \
        : "=r"(__result), "+x"(ptr)             \
    );                                          \
    __result;                                   \
}))


#define ST_XPLUS(ptr,val) do {               \
  __asm__ __volatile__ (			\
    "st x+,%1			        \n\t"   \
    :"+x"(ptr):"r"(val)                  \
  );						\
} while(0)

#define STORE_TO_XPLUS(var) do {		\
  __asm__ __volatile__ (			\
    "st	   X+, %0\n\t"	                        \
    ::"r"(var):"r26","r27"                      \
  );						\
} while(0)


#define ADDRESS_TO_XPLUS(addr) do {		\
  __asm__ __volatile__ (			\
    "lds   __tmp_reg__," QUOTE(addr) "	\n\t"	\
    "st	   X+, __tmp_reg__		\n\t"	\
  );						\
} while(0)


#define XPLUS_TO_ADDRESS(addr) do {		\
  __asm__ __volatile__ (			\
    "ld	   __tmp_reg__, X+		\n\t"	\
    "sts   " QUOTE(addr) ", __tmp_reg__	\n\t"	\
  );						\
} while(0)


#define STORE_XPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   X+, %2\n\t"                          \
    :"+x"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

// ----------------------------------------------
// Operations with Y register
// ----------------------------------------------

#define LOAD_YPLUS(ptr)			        \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, y+\n\t"                             \
        : "=r"(__result), "+y"(ptr)             \
    );                                          \
    __result;                                   \
}))

#define ADDRESS_TO_YPLUS(addr) do {		\
  __asm__ __volatile__ (			\
    "lds   __tmp_reg__," QUOTE(addr) "	\n\t"	\
    "st	   Y+, __tmp_reg__		\n\t"	\
  );						\
} while(0)


#define YPLUS_TO_ADDRESS(addr) do {		\
  __asm__ __volatile__ (			\
    "ld	   __tmp_reg__, Y+		\n\t"	\
    "sts   " QUOTE(addr) ", __tmp_reg__	\n\t"	\
  );						\
} while(0)


#define LD_YPLUS(result,ptr) do {               \
  __asm__ __volatile__ (			\
    "ld	%0, y+			        \n\t"   \
    : "=r" (result) : "y"(ptr)                  \
  );						\
} while(0)


#define LDD_Y(result, d) do {                   \
  __asm__ __volatile__ (			\
    "ldd   %0,Y + " QUOTE(d) "          \n\t"   \
    : "=r" (result)                             \
  );						\
} while(0)


#define LDD_Y_U16(result, d) do {               \
  __asm__ __volatile__ (			\
    "ldd   %A0,Y + " QUOTE(d) "          \n\t"  \
    "ldd   %B0,Y + " QUOTE(d) " + 1      \n\t"  \
    : "=r" (result)                             \
  );						\
} while(0)


#define ST_YPLUS(var) do {                      \
  __asm__ __volatile__ (                        \
    "st	   Y+, %0\n\t"                          \
    ::"r"(var):"r28","r29"                      \
  );						\
} while(0)


#define STORE_YPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   Y+, %2\n\t"                          \
    :"+y"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

// ----------------------------------------------
// Operations with Z register
// ----------------------------------------------

#define LOAD_ZPLUS(ptr)			        \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, z+\n\t"                             \
        : "=r"(__result), "+z"(ptr)             \
    );                                          \
    __result;                                   \
}))


#define LD_ZPLUS(result,ptr) do {               \
  __asm__ __volatile__ (			\
    "ld	%0, z+			        \n\t"   \
    : "=r" (result),"+z"(ptr)                   \
  );						\
} while(0)


#define LDD_Z(result, d) do {                   \
  __asm__ __volatile__ (			\
    "ldd   %0,Z + " QUOTE(d) "          \n\t"   \
    : "=r" (result)                             \
  );						\
} while(0)


#define LDD_Z_U16(result, d) do {               \
  __asm__ __volatile__ (			\
    "ldd   %A0,Z + " QUOTE(d) "          \n\t"  \
    "ldd   %B0,Z + " QUOTE(d) " + 1      \n\t"  \
    : "=r" (result)                             \
  );						\
} while(0)


#define STORE_ZPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   z+, %2\n\t"                          \
    :"+z"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

// ----------------------------------------------
// Transfers between X, Y and Z register
// ----------------------------------------------

#define YPLUS_TO_ZPLUS() do {			\
  __asm__ __volatile__ (			\
    "ld	__tmp_reg__, Y+			\n\t"   \
    "st	Z+, __tmp_reg__			\n\t"   \
  );						\
} while(0)


// ----------------------------------------------
// Flash access
// ----------------------------------------------


#define __LPM_increment__(addr) \
(__extension__({                \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm %0, Z+" "\n\t"     \
        : "=r" (__result),      \
          "+z" (addr)           \
    );                          \
    __result;                   \
}))

#define __LPM_word__(addr)      \
(__extension__({                \
    uint16_t __result;          \
    __asm__                     \
    (                           \
        "lpm %A0, Z+" "\n\t"    \
        "lpm %B0, Z+" "\n\t"    \
        : "=r" (__result),      \
          "+z" (addr)           \
    );                          \
    __result;                   \
}))


#define ADIW(to,k)		    do { __asm__ __volatile__ ("adiw %0, %1" : "=w"(to) : "I"((k))); } while(0)
#define MOVW(to,from)		do { __asm__ __volatile__ ("movw %0, %1" : "=r"(to) : "r"(from)); } while(0)

#define LDI(k)			    do { __asm__ __volatile__ ("ldi r24, %1" :: "r"(k)) : "r24"; } while(0)
#define MOV(to,from)		do { __asm__ __volatile__ ("mov  %0, %1" : "=r"(to) : "r"(from)); } while(0)
#define CLR(reg)		    do { __asm__ __volatile__ ("clr  %0" : "+r"(reg)); } while(0)
#define INC(reg)		    do { __asm__ __volatile__ ("inc  %0" : "=r"(reg) : "r"(reg)); } while(0)
#define DEC(reg)		    do { __asm__ __volatile__ ("dec  %0" : "=r"(reg) : "r"(reg)); } while(0)
#define ROR(reg)		    do { __asm__ __volatile__ ("ror  %0" : "=r"(reg) : "r"(reg)); } while(0)
#define ROL(reg)		    do { __asm__ __volatile__ ("rol  %0" : "=r"(reg) : "r"(reg)); } while(0)

#define BREQ(label)		    do { __asm__ __volatile__ ("breq " #label); } while(0)
#define BRNE(label)		    do { __asm__ __volatile__ ("brne " #label); } while(0)

#define RJMP(label)		    do { __asm__ __volatile__ ("rjmp " #label); } while(0)
#define RETI()		        do { __asm__ __volatile__ ("reti"); } while(0)

#define BRNE_TMP_LABEL()    do { __asm__ __volatile__("brne " MARKED_LABEL(L, QUOTE(__LINE__))); } while(0)
#define IF_ZERO(body)       do { BRNE_TMP_LABEL(); body; MARK0(MARKED_LABEL(L, QUOTE(__LINE__))); } while(0)


#define __IN(result, addr)              \
    __asm__                             \
    (                                   \
        "in %0, %1" "\n\t"              \
        : "=r" (result)                 \
        : "I" (_SFR_IO_ADDR(addr))      \
    );                          

#define __OUT(addr, value)              \
    __asm__                             \
    (                                   \
        "out %0, %1" "\n\t"             \
        :                               \
        :"I" (_SFR_IO_ADDR(addr)),      \
         "r" (value)                    \
    );                          

#endif // __CPU__AVR__ASM_H
