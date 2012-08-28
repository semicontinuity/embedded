#ifndef __CPU__AVR__ASM_H
#define __CPU__AVR__ASM_H

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
#define MARK(label)		        do { __asm__ __volatile__( label ":"); } while(0)


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


// ----------------------------------------------
// Operations with X register
// ----------------------------------------------

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


// ----------------------------------------------
// Operations with Y register
// ----------------------------------------------

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
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm %0, Z+" "\n\t"     \
        : "=r" (__result),      \
          "+z" (__addr16)       \
    );                          \
    __result;                   \
}))


#define ADIW(to,k)		do { __asm__ __volatile__ ("adiw %0, %1" : "=w"(to) : "I"((k))); } while(0)
#define MOVW(to,from)		do { __asm__ __volatile__ ("movw %0, %1" : "=r"(to) : "r"(from)); } while(0)

#define LDI(k)			do { __asm__ __volatile__ ("ldi r24, %1" :: "r"(k)) : "r24"; } while(0)
#define MOV(to,from)		do { __asm__ __volatile__ ("mov  %0, %1" : "=r"(to) : "r"(from)); } while(0)
#define CLR(reg)		do { __asm__ __volatile__ ("clr  %0" : "+r"(reg)); } while(0)
#define INC(reg)		do { __asm__ __volatile__ ("inc  %0" : "=r"(reg) : "r"(reg)); } while(0)
#define DEC(reg)		do { __asm__ __volatile__ ("dec  %0" : "=r"(reg) : "r"(reg)); } while(0)
#define BREQ(label)		do { __asm__ __volatile__ ("breq " #label); } while(0)
#define BRNE(label)		do { __asm__ __volatile__ ("brne " #label); } while(0)

#define RETI()		        do { __asm__ __volatile__ ("reti"); } while(0)

#define BRNE_TMP_LABEL()        do { __asm__ __volatile__("brne " TMP_LABEL(L)); } while(0)
#define IF_ZERO(body)           do { BRNE_TMP_LABEL(); body; MARK(TMP_LABEL(L)); } while(0)

#endif // __CPU__AVR__ASM_H