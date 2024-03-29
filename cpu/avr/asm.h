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


#define FIX_REGISTER(r)                 __asm__ __volatile__("" : "=r" (r) : "r" (r));

#define FIX_LOWER_REGISTER(r)           __asm__ __volatile__("" : "=l" (r) : "l" (r));

#define FIX_TEMP_REGISTER(r)            (__extension__({        \
    register uint8_t __result asm("r0");                        \
    __result = r;                                               \
    __asm__ __volatile__("" : "=t" (__result) : "0" (__result));\
    __result;                                                   \
}))


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
#define MARK0(label)                    do { __asm__ __volatile__( label ":"); } while(0)


#define ZERO_REG(var)    do {                           \
  __asm__ __volatile__ (                                \
    "mov %0, r1\n\t"                                    \
    : "=d"(var)                                         \
    :                                                   \
  );                                                    \
} while(0)


#define __CLT() do {                                    \
  asm volatile (                                        \
    "clt\r\n"                                           \
  );                                                    \
} while(0)

#define __SET() do {                                    \
  asm volatile (                                        \
    "set\r\n"                                           \
  );                                                    \
} while(0)

#define __BST(src, srcbit) do {                         \
  asm volatile (                                        \
    "bst  %0, %1 \r\n"                                  \
    :                                                   \
    : "r" (src),                                        \
      "I" (srcbit)                                      \
  );                                                    \
} while(0)

#define __BLD(dst, dstbit) do {                         \
  asm volatile (                                        \
    "bld  %0, %1 \r\n"                                  \
    : "+r" (dst)                                        \
    : "I" (dstbit)                                      \
  );                                                    \
} while(0)

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


// not optimal: uses extra register for k
#define SUB_LO8(var, k)	do {            \
  __asm__ __volatile__ (                \
    "sub %A0, %1\n\t"                   \
        : "=d"(var)                     \
        : "d"(k)                        \
  );                                    \
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


#define SET_HI8_OF(u16_dst, src)	do {	\
  __asm__ __volatile__ (			\
    "mov %B0, %B1	\n\t"			\
        : "=r"(u16_dst) : "r"(src)		\
  );						\
} while(0)


#define GOTO_IF_BIT_SET(r, b, l) do {	                    \
  __asm__ __volatile__ (		                            \
    "sbis %0, %1\n\t"			                            \
    "rjmp " #l "\n\t"			                            \
        :				                                    \
        : "I"(_SFR_IO_ADDR(r)),		                        \
          "I"(b)			                                \
  );					                                    \
} while(0)


#define IF_BIT_SET_INC(r, v, bit) do {                      \
    __asm__ __volatile__(                                   \
    "sbrc %1, %2\n\t"                                       \
    "inc %0\n\t"                                            \
        : "=r"((r))                                         \
        : "r"((v)),                                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_BIT_SET_DEC(r, v, bit) do {                      \
    __asm__ __volatile__(                                   \
    "sbrc %1, %2\n\t"                                       \
    "dec %0\n\t"                                            \
        : "=r"((r))                                         \
        : "r"((v)),                                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_BIT_CLEAR_INC(r, v, bit) do {                    \
    __asm__ __volatile__(                                   \
    "sbrs %1, %2\n\t"                                       \
    "inc %0\n\t"                                            \
        : "=r"((r))                                         \
        : "r"((v)),                                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_BIT_CLEAR_DEC(r, v, bit) do {                    \
    __asm__ __volatile__(                                   \
    "sbrs %1, %2\n\t"                                       \
    "dec %0\n\t"                                            \
        : "=r"((r))                                         \
        : "r"((v)),                                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)




#define IF_BIT_SET_INC_ELSE_DEC(r, v, bit) do {             \
    __asm__ __volatile__(                                   \
    "inc  %0\n\t"                                           \
    "sbrs %1, %2\n\t"                                       \
    "subi %0, 2\n\t"                                        \
        : "=d"((r)),                                        \
          "+r"((v))                                         \
        : "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_BIT_CLEAR_INC_ELSE_DEC(r, v, bit) do {           \
    __asm__ __volatile__(                                   \
    "inc  %0\n\t"                                           \
    "sbrc %1, %2\n\t"                                       \
    "subi %0, 2\n\t"                                        \
        : "=d"((r)),                                        \
          "+r"((v))                                         \
        :  "I"((bit))                                       \
    );                                                      \
} while (0)


#define IF_IO_BIT_SET_INC_ELSE_DEC(r, ioreg, bit) do {      \
    __asm__ __volatile__(                                   \
    "inc  %0\n\t"                                           \
    "sbis %1, %2\n\t"                                       \
    "subi %0, 2\n\t"                                        \
        : "=d"((r)),                                        \
        : "I"(_SFR_IO_ADDR(ioreg)),                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_IO_BIT_CLEAR_INC_ELSE_DEC(r, ioreg, bit) do {    \
    __asm__ __volatile__(                                   \
    "inc  %0\n\t"                                           \
    "sbic %1, %2\n\t"                                       \
    "subi %0, 2\n\t"                                        \
        : "=d"((r)),                                        \
        : "I"(_SFR_IO_ADDR(ioreg)),                         \
          "I"((bit))                                        \
    );                                                      \
} while (0)

#define IF_BIT_SET_LOAD_A_ELSE_B(r, v, bit, a, b) do {      \
    __asm__ __volatile__(                                   \
    "ldi  %0, %3\n\t"                                       \
    "sbrs %1, %2\n\t"                                       \
    "ldi  %0, %4\n\t"                                       \
        : "=d"((r)),                                        \
          "=r"((v))                                         \
        :  "I"((bit)),                                      \
          "M"((uint8_t)((a) & 0xFF)),                       \
          "M"((uint8_t)((b) & 0xFF))                        \
    );                                                      \
} while (0)

#define IF_BIT_SET_CONST_A_ELSE_CONST_B(v, bit, a, b)       \
(__extension__({                                            \
    uint8_t __result;                                       \
    __asm__ __volatile__(                                   \
    "ldi  %0, %3\n\t"                                       \
    "sbrs %1, %2\n\t"                                       \
    "ldi  %0, %4\n\t"                                       \
        : "=d"(__result),                                   \
          "=r"((v))                                         \
        : "I"((bit)),                                       \
          "M"((a) & 0xFF),                                  \
          "M"((b) & 0xFF)                                   \
    );                                                      \
    __result;                                               \
}))


#define IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(ioreg, bit, a, b)\
(__extension__({                                            \
    uint8_t __result;                                       \
    __asm__ __volatile__(                                   \
    "ldi  %0, %3\n\t"                                       \
    "sbis %1, %2\n\t"                                       \
    "ldi  %0, %4\n\t"                                       \
        : "=d"(__result)                                    \
        : "I"(_SFR_IO_ADDR(ioreg)),                         \
          "I"((bit)),                                       \
          "M"((a)),                                         \
          "M"((b))                                          \
    );                                                      \
    __result;                                               \
}))

#define SET_BIT_IF_IO_BIT_IS_SET(r, rbit, ioreg, ioregbit) do { \
    __asm__ __volatile__(                                   \
        "sbic %2, %3\n\t"                                   \
        "sbr %0, %1\n\t"                                    \
        : "=r"((r))                                         \
        : "I"((rbit)),                                      \
          "I"(_SFR_IO_ADDR(ioreg)),                         \
          "I"(ioregbit)                                     \
    );                                                      \
} while (0)

#define OUT_BIT(ioreg, ioregbit, r, rbit) do {              \
    __asm__ __volatile__(                                   \
        "sbrc %0, %1\n\t"                                   \
        "sbi %2, %3\n\t"                                    \
        "sbrs %0, %1\n\t"                                   \
        "cbi %2, %3\n\t"                                    \
        :                                                   \
        : "r"((r)),                                         \
          "I"((rbit)),                                      \
          "I"(_SFR_IO_ADDR(ioreg)),                         \
          "I"(ioregbit)                                     \
    );                                                      \
} while (0)


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


#define IF_LO8_EQUAL_EXEC_1_OP(v1, v2, code) do {           \
  __asm__ __volatile__(                                     \
    "cpse %A0, %A1\n\t"                                     \
    "cpse r0, r0\n\t"                                       \
    :                                                       \
    : "r"(v1),                                              \
      "r"(v2)                                               \
  );                                                        \
  do {code;} while(0);                                      \
} while(0)


#define IF_LO8_EQUAL_CLEAR_IO_BIT(v1, v2, addr, bit) do {   \
  __asm__ __volatile__(                                     \
    "cpse %A0, %A1\n\t"                                     \
    "cpse r0, r0\n\t"                                       \
    "cbi  %2, %3\n\t"                                       \
    :                                                       \
    : "r"(v1),                                              \
      "r"(v2),                                              \
      "I"(_SFR_IO_ADDR(addr)),                              \
      "I"(bit)                                              \
  );                                                        \
} while(0)


#define IF_LO8_EQUAL_SET_IO_BIT(v1, v2, addr, bit) do {     \
  __asm__ __volatile__(                                     \
    "cpse %A0, %A1\n\t"                                     \
    "cpse r0, r0\n\t"                                       \
    "sbi  %2, %3\n\t"                                       \
    :                                                       \
    : "r"(v1),                                              \
      "r"(v2),                                              \
      "I"(_SFR_IO_ADDR(addr)),                              \
      "I"(bit)                                              \
  );                                                        \
} while(0)


#define LOOP_WHILE_LO8_EQUAL(v1, v2) do {       \
  __asm__ __volatile__(                         \
    "L_" QUOTE(__LINE__) ":\n\t"                \
    "cp %A0, %A1\n\t"                           \
    "breq L_" QUOTE(__LINE__) "\n\t"            \
        :                                       \
        : "r"(v1),"r"(v2)                       \
  );					                        \
} while(0)


// ----------------------------------------------
// Operations with X register
// ----------------------------------------------

#define INIT_X(k)                               \
(__extension__({                                \
    uint16_t __result;                          \
    __asm__ __volatile__ (                      \
        "ldi %A0, %1\n\t"			            \
        "ldi %B0, %2\n\t"			            \
            : "=x"(__result)			        \
            : "M"((uint8_t)((k) & 0xFF)),	    \
              "M"((uint8_t)((k) >> 8))          \
    );                                          \
    __result;                                   \
}))

#define LOAD_XPLUS(ptr)			                \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, x+\n\t"                             \
    : "=r"(__result), "+x"(ptr)                 \
    );                                          \
    __result;                                   \
}))


#define ST_XPLUS(ptr, var) do {                 \
  __asm__ __volatile__ (			            \
    "st    x+, %2\n\t"                          \
    :"+x"(ptr)                                  \
    :"0"(ptr),"r"(var)                          \
  );						                    \
} while(0)

#define STORE_XPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   X+, %2\n\t"                          \
    :"+x"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

#define STORE_TO_XPLUS(var) do {		        \
  __asm__ __volatile__ (			            \
    "st	   X+, %0\n\t"	                        \
    ::"r"(var):"r26","r27"                      \
  );						                    \
} while(0)


#define ADDRESS_TO_XPLUS(addr) do {		        \
  __asm__ __volatile__ (			            \
    "lds   __tmp_reg__," QUOTE(addr) "	\n\t"	\
    "st	   X+, __tmp_reg__		\n\t"	        \
  );						                    \
} while(0)


#define XPLUS_TO_ADDRESS(addr) do {		        \
  __asm__ __volatile__ (			            \
    "ld	   __tmp_reg__, X+		\n\t"	        \
    "sts   " QUOTE(addr) ", __tmp_reg__	\n\t"	\
  );						                    \
} while(0)


// ----------------------------------------------
// Operations with Y register
// ----------------------------------------------

#define INIT_Y(k)                               \
(__extension__({                                \
    uint16_t __result;                          \
    __asm__ __volatile__ (                      \
        "ldi %A0, %1\n\t"			            \
        "ldi %B0, %2\n\t"			            \
            : "=y"(__result)			        \
            : "M"((uint8_t)((k) & 0xFF)),	    \
              "M"((uint8_t)((k) >> 8))          \
    );                                          \
    __result;                                   \
}))

#define LOAD_Y_OFFSET(ptr, d)                   \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ldd %0, y + " QUOTE(d) "\n\t"              \
        : "=r"(__result), "+y"(ptr)             \
    );                                          \
    __result;                                   \
}))

#define STORE_Y_OFFSET(ptr, d, var) do {        \
  __asm__ __volatile__ (                        \
    "std y + " QUOTE(d) ", %1\n\t"              \
    :"+y"(ptr)                                  \
    :"r"(var)                                   \
  );                                            \
} while(0)

#define LOAD_YPLUS(ptr)			                \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, y+\n\t"                             \
        : "=r"(__result), "+y"(ptr)             \
    );                                          \
    __result;                                   \
}))

#define ADDRESS_TO_YPLUS(addr) do {		        \
  __asm__ __volatile__ (			            \
    "lds   __tmp_reg__," QUOTE(addr) "	\n\t"	\
    "st	   Y+, __tmp_reg__		\n\t"	        \
  );						                    \
} while(0)


#define YPLUS_TO_ADDRESS(addr) do {		        \
  __asm__ __volatile__ (			            \
    "ld	   __tmp_reg__, Y+		\n\t"	        \
    "sts   " QUOTE(addr) ", __tmp_reg__	\n\t"	\
  );						                    \
} while(0)


#define LD_YPLUS(result,ptr) do {               \
  __asm__ __volatile__ (			            \
    "ld	%0, y+			        \n\t"           \
    : "=r" (result) : "y"(ptr)                  \
  );						                    \
} while(0)


#define LDD_Y(result, d) do {                   \
  __asm__ __volatile__ (			            \
    "ldd   %0,Y + " QUOTE(d) "          \n\t"   \
    : "=r" (result)                             \
  );						                    \
} while(0)


#define LDD_Y_U16(result, d) do {               \
  __asm__ __volatile__ (			            \
    "ldd   %A0,Y + " QUOTE(d) "          \n\t"  \
    "ldd   %B0,Y + " QUOTE(d) " + 1      \n\t"  \
    : "=r" (result)                             \
  );						                    \
} while(0)


#define ST_YPLUS(ptr, var) do {                 \
  __asm__ __volatile__ (			            \
    "st    y+, %2\n\t"                          \
    :"+y"(ptr)                                  \
    :"0"(ptr),"r"(var)                          \
  );						                    \
} while(0)


#define STORE_YPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   Y+, %2\n\t"                          \
    :"+y"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

// Document, why these variable specs are used
#define STORE_PLUS_VIA_Y(ptr, var) do {         \
  __asm__ __volatile__ (			            \
    "st	y+, %1			        \n\t"           \
    : "+y"(ptr) : "r"(var)                      \
  );						                    \
} while(0)


// ----------------------------------------------
// Operations with Z register
// ----------------------------------------------

#define LOAD_Z_OFFSET(ptr, d)                   \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ldd %0, z + " QUOTE(d) "\n\t"              \
        : "=r"(__result), , "+z"(ptr)           \
    );                                          \
    __result;                                   \
}))


#define STORE_Z_OFFSET(ptr, d, var) do {        \
  __asm__ __volatile__ (                        \
    "st	z + " QUOTE(d) ", %1\n\t"               \
    :"+z"(ptr)                                  \
    :"r"(var)                                   \
  );                                            \
} while(0)

#define LOAD_ZPLUS(ptr)			                \
(__extension__({                                \
    uint8_t __result;                           \
    __asm__ (                                   \
    "ld %0, z+\n\t"                             \
        : "=r"(__result), "+z"(ptr)             \
    );                                          \
    __result;                                   \
}))


#define LD_ZPLUS(result,ptr) do {               \
  __asm__ __volatile__ (			            \
    "ld	%0, z+			        \n\t"           \
    : "=r" (result),"+z"(ptr)                   \
  );						                    \
} while(0)


#define LDD_Z(result, d) do {                   \
  __asm__ __volatile__ (			            \
    "ldd   %0,Z + " QUOTE(d) "          \n\t"   \
    : "=r" (result)                             \
  );						                    \
} while(0)


#define LDD_Z_U16(result, d) do {               \
  __asm__ __volatile__ (			            \
    "ldd   %A0,Z + " QUOTE(d) "          \n\t"  \
    "ldd   %B0,Z + " QUOTE(d) " + 1      \n\t"  \
    : "=r" (result)                             \
  );						                    \
} while(0)


#define ST_ZPLUS(ptr, var) do {                 \
  __asm__ __volatile__ (			            \
    "st    z+, %2\n\t"                          \
    :"+z"(ptr)                                  \
    :"0"(ptr),"r"(var)                          \
  );						                    \
} while(0)

#define STORE_ZPLUS(ptr, var) do {              \
  __asm__ __volatile__ (                        \
    "st	   z+, %2\n\t"                          \
    :"+z"(ptr)                                  \
    :"0"(ptr), "r"(var)                         \
  );                                            \
} while(0)

// Document, why these variable specs are used
#define STORE_PLUS_VIA_Z(ptr, var) do {         \
  __asm__ __volatile__ (			            \
    "st	z+, %1			        \n\t"           \
    : "+z"(ptr) : "r"(var)                      \
  );						                    \
} while(0)


// ----------------------------------------------
// Transfers between X, Y and Z register
// ----------------------------------------------

#define YPLUS_TO_ZPLUS() do {			\
  __asm__ __volatile__ (			    \
    "ld	__tmp_reg__, Y+			\n\t"   \
    "st	Z+, __tmp_reg__			\n\t"   \
  );						            \
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
#define ANDI(reg, k)		do { __asm__ __volatile__ ("andi %0, %1" : "+d"(reg) : "M"((k))) ; } while(0)
#define ORI(reg, k)			do { __asm__ __volatile__ ("ori  %0, %1" : "+d"(reg) : "M"((k))) ; } while(0)
#define MOV(to,from)		do { __asm__ __volatile__ ("mov  %0, %1" : "=r"(to) : "r"(from)); } while(0)
#define CLR(reg)		    do { __asm__ __volatile__ ("clr  %0" : "+r"(reg)); } while(0)
#define LSR(reg)		    do { __asm__ __volatile__ ("lsr  %0" : "+r"(reg)); } while(0)
#define LSL(reg)		    do { __asm__ __volatile__ ("lsl  %0" : "+r"(reg)); } while(0)
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


#define __MOV(r)                        \
(__extension__({                        \
    register uint8_t __result;          \
    __asm__ __volatile__ (              \
        "mov %0, %1"                    \
        : "=r"(__result) : "r"(r)       \
    );                                  \
    __result;                           \
}))


#define __DEC(r)			            \
(__extension__({                        \
    __asm__ __volatile__ (              \
        "dec %0"                        \
        : "=r"(r) : "r"(r)              \
    );                                  \
    r;                                  \
}))


#define __IN(result, addr) do {         \
    __asm__ __volatile__                \
    (                                   \
        "in %0, %1" "\n\t"              \
        : "=r" (result)                 \
        : "I" (_SFR_IO_ADDR(addr))      \
    );                                  \
  } while(0)

#define __OUT(addr, value)              \
    __asm__                             \
    (                                   \
        "out %0, %1" "\n\t"             \
        :                               \
        :"I" (_SFR_IO_ADDR(addr)),      \
         "r" (value)                    \
    );                          

#define __LDS(result, addr)             \
    do { __asm__ __volatile__           \
    (                                   \
        "lds %0, %1" "\n\t"             \
        : "=r" (result)                 \
        : "i" (_SFR_MEM_ADDR(addr))     \
    ); } while(0)

#define __STS(addr, value)              \
    do { __asm__ __volatile__           \
    (                                   \
        "sts %0, %1" "\n\t"             \
        :                               \
        :"i" (_SFR_MEM_ADDR(addr)),     \
         "r" (value)                    \
    ); } while(0)



#if defined(TEMP_REG)

#define LD_IO_REG(result, ptr) do {                 \
    if (_SFR_IO_ADDR(ptr) < 0x40) {                 \
        __IN(result, ptr);                          \
    } else {                                        \
        __LDS(result, ptr);                         \
    }                                               \
} while(0)

#define ST_IO_REG(ptr, result) do {                 \
    if (_SFR_IO_ADDR(ptr) < 0x40) {                 \
        __OUT(ptr, result);                         \
    } else {                                        \
        __STS(ptr, result);                         \
    }                                               \
} while(0)

#endif


// Clobbers T bit
#define CLEAR_BIT_IN_IO_REG(ptr, bit) do {          \
    if (_SFR_IO_ADDR(ptr) < 0x20) {                 \
        ptr &= (1 << (bit));                        \
    } else if (_SFR_IO_ADDR(ptr) < 0x40) {          \
        uint8_t temp;                               \
        __IN(temp, ptr);                            \
        __CLT();                                    \
        __BLD(temp, bit);                           \
        __OUT(ptr, temp);                           \
    } else {                                        \
        uint8_t temp;                               \
        __LDS(temp, ptr);                           \
        __CLT();                                    \
        __BLD(temp, bit);                           \
        __STS(ptr, temp);                           \
    }                                               \
} while(0)


#if defined(TEMP_REG) && TEMP_REG > 15
#define ANDI_IO_REG(ptr, mask) do {                 \
    if (_SFR_IO_ADDR(ptr) < 0x20) {                 \
        ptr &= mask;                                \
    } else if (_SFR_IO_ADDR(ptr) < 0x40) {          \
        register uint8_t temp asm(QUOTE(TEMP_REG)); \
        __IN(temp, ptr);                            \
        temp &= mask;                               \
        __OUT(ptr, temp);                           \
    } else {                                        \
        register uint8_t temp asm(QUOTE(TEMP_REG)); \
        __LDS(temp, ptr);                           \
        temp &= mask;                               \
        __STS(ptr, temp);                           \
    }                                               \
} while(0)
#else
#define ANDI_IO_REG(ptr, mask) do {                 \
    ptr &= mask;                                    \
} while(0)
#endif


// Clobbers T bit
#define SET_BIT_IN_IO_REG(ptr, bit) do {            \
    if (_SFR_IO_ADDR(ptr) < 0x20) {                 \
        ptr &= (1 << (bit));                        \
    } else if (_SFR_IO_ADDR(ptr) < 0x40) {          \
        uint8_t temp;                               \
        __IN(temp, ptr);                            \
        __SET();                                    \
        __BLD(temp, bit);                           \
        __OUT(ptr, temp);                           \
    } else {                                        \
        uint8_t temp;                               \
        __LDS(temp, ptr);                           \
        __SET();                                    \
        __BLD(temp, bit);                           \
        __STS(ptr, temp);                           \
    }                                               \
} while(0)


#if defined(TEMP_REG) && TEMP_REG > 15
#define ORI_IO_REG(ptr, mask) do {                 \
    if (_SFR_IO_ADDR(ptr) < 0x20) {                 \
        ptr |= mask;                                \
    } else if (_SFR_IO_ADDR(ptr) < 0x40) {          \
        register uint8_t temp asm(QUOTE(TEMP_REG)); \
        __IN(temp, ptr);                            \
        temp |= mask;                               \
        __OUT(ptr, temp);                           \
    } else {                                        \
        register uint8_t temp asm(QUOTE(TEMP_REG)); \
        __LDS(temp, ptr);                           \
        temp |= mask;                               \
        __STS(ptr, temp);                           \
    }                                               \
} while(0)
#else
#define ORI_IO_REG(ptr, mask) do {                 \
    ptr |= mask;                                    \
} while(0)
#endif


#endif // __CPU__AVR__ASM_H
