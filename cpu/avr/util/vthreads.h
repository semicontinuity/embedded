#ifndef __VTHREADS_H__
#define __VTHREADS_H__

/**
 * \file
 * Virtual threads implementation for AVR microcontrollers.
 * Inspired by Protothreads library: http://dunkels.com/adam/pt/
 *
 * With some optimizations, provides faster thread switching.
 *
 * Differences to Protothreads:
 *  - Virtual thread functions do not have take 'thread' argument - ususally they can serve only one thread.
 *  - Virtual thread functions must have 'void' return type - thus it is possible to use inside interrupt handlers.
 *  - Virtual thread runs forever over and over - if the thread has finished or waiting, and it is not necessary to schedule
 *    the thread function, it should communicate this to scheduler via some shared variable.
 *  - Virtual thread functions do not reference thread's data via pointer - thus it is possible to place it to the registers.
 *  - It is possible to move the instruction pointer of the virtual thread by seeking to the specified mark in the thread function.
 *
 * Supported compiler: avr-gcc, or any other with support for address labels.
 *
 * Please refer to Protothreads documentation for usage details and concepts behind implementation.
 * \author semicontinuity
 */


/**
 * A virtual thread instruction pointer type.
 * Stores the continuation of the thread (the address, from which the virtual thread function will proceed).
 * For good performance, place it to the general purpose I/O register.
 * For better performance, place it in the register r2-r14. Define VTHREADS__FAST_RESUME and/or VTHREADS__FAST_YIELD for even higher speed.
 * For best performance, place it in the high register (r16-r24). Define VTHREADS__FAST_RESUME for even higher speed.
 * For utmost performance, place it to r30. Beware of other code that may use r30:r31, such as PROGMEM data access (lpm instruction).
 */
typedef void * vthread_ip_t;

#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif

#define FC_LABEL(thread, mark)          #thread "__" QUOTE(mark)
#define FC_LABEL_BEGIN(thread)          FC_LABEL(thread, BEGIN)
#define FC_LABEL_END(thread)	        FC_LABEL(thread, END)

#define FC_ASM_LABEL(label)             do { __asm__ __volatile__( label ":"); } while(0)

#define FC_ASM_LABEL_ADDRESS(label)	                                                        \
(__extension__({                                                                            \
  uint16_t __result;                                                                        \
  __asm__ __volatile__ (		                                                            \
    "ldi %A0, pm_lo8(" label ")\n\t"	                                                    \
    "ldi %B0, pm_hi8(" label ")\n\t"	                                                    \
        : "=d"(__result)		                                                            \
  );					                                                                    \
  __result;                                                                                 \
}))

#define FC_ASM_LOAD_LABEL_ADDRESS(var,label)	do {                                        \
  __asm__ __volatile__ (		                                                            \
    "ldi %A0, pm_lo8(" label ")\n\t"	                                                    \
    "ldi %B0, pm_hi8(" label ")\n\t"	                                                    \
        : "=d"(var)                                                                         \
  );					                                                                    \
} while(0);

#define FC_ASM_RESUME_Z(ip)                                                                 \
(__extension__({                                                                            \
    __asm__ __volatile__("ijmp"                                                             \
        : "=z" (ip)                                                                         \
        : "0" (ip)                                                                          \
    );                                                                                      \
  ip;                                                                                       \
}))

#define FC_POINTER(label) ((void*)FC_ASM_LABEL_ADDRESS(label))



#ifdef VTHREADS__FAST_RESUME

#define FC_RESUME(s)			\
  do {					\
      void *ip_copy;                    \
      ip_copy = s;                      \
      __asm__ __volatile__(             \
          ""                            \
          : "=z" (ip_copy)              \
          : "0" (ip_copy)               \
      );                                \
      goto *ip_copy;                    \
  } while(0)

#else

#define FC_RESUME(s)			                                                            \
  do {					                                                                    \
      goto *s;                                                                              \
  } while(0)

#endif


#define FC_CONCAT2(s1, s2) s1##s2
#define FC_CONCAT(s1, s2) FC_CONCAT2(s1, s2)



/**
 * Place a named mark (label) in the virtual thread.
 * Seek operations on the thread can be used to set the thread's instruction pointer
 * to the position with the specified mark.
 * \param thread  The name of the virtual thread
 * \param mark    The name of the mark
 */
#define VT_MARK(thread, mark)                                                               \
mark:                                                                                       \
  (void)&&mark;                                                                             \
  FC_ASM_LABEL(FC_LABEL(thread, mark));


/**
 * Set the instruction pointer of the given virtual thread to the specified mark.
 * \param thread  A virtual thread name
 * \param ip      An instruction pointer of the virtual thread
 * \param mark    The name of the mark
 */
#define VT_SEEK(thread, ip, mark) do {                                                      \
  FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL(thread, mark));                                    \
} while(0)


/**
 * Initialize the virtual thread.
 *
 * This macro MUST be called before the first call to the virtual thread function.
 * \param thread  A name of the virtual thread
 * \param ip      An instruction pointer of the virtual thread
 */
#define VT_INIT(thread, ip) do {                                                            \
  FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL_BEGIN(thread));                                    \
} while(0)


/**
 * Restart the virtual thread.
 * \param thread  A name of the virtual thread
 * \param ip      An instruction pointer of the virtual thread
 */
#define VT_RESTART(thread, ip) VT_INIT(thread, ip)


/**
* Declare the start of a virtual thread inside the function implementing the virtual thread.
* \param thread  A virtual thread variable
* \param ip      An instruction pointer of the virtual thread
*/
#define VT_LOOP_BEGIN(thread, ip) do {                                                      \
  char vt_flag = 1;                                                                         \
  FC_RESUME(ip);                                                                            \
  {\
    for (;;) {\
        VT_MARK(thread, BEGIN)\

/**
 * Declare the start of a virtual thread inside the function implementing the virtual thread.
 * \param thread  A virtual thread variable
 * \param ip      An instruction pointer of the virtual thread
 */
#define VT_BEGIN(thread, ip) do {                                                           \
  char vt_flag = 1;                                                                         \
  FC_RESUME(ip);                                                                            \
  {                                                                                         \
      VT_MARK(thread, BEGIN);


/**
 * Declare the end of a virtual thread.
 * \param thread A virtual thread name
 */
#define VT_END(thread)                                                                      \
  }                                                                                         \
  VT_MARK(thread, END);                                                                     \
  (void)vt_flag;                                                                            \
} while(0)


#define VT_LOOP_END(thread)                                                                 \
    }                                                                                       \
  }                                                                                         \
} while(0)


#define VT_UNREACHEABLE_END(thread)                                                         \
  }                                                                                         \
} while(0)


#define VT_BREAK(thread)                                                                    \
  goto END;

/**
 * Yield control from the current virtual thread.
 * Once the virtual thread function is called again, it will resume from the following operator.
 * \param thread  A virtual thread name
 * \param ip      An instruction pointer of the virtual thread
 */
#ifdef VTHREADS__FAST_YIELD

#define VT_YIELD(thread, ip)                                    \
do {                                                            \
FC_CONCAT(YIELD, __LINE__):                                     \
  (void)&&FC_CONCAT(YIELD, __LINE__);                           \
  vt_flag = 0;				                        \
  FC_CONCAT(RESUME, __LINE__):                                  \
  if(vt_flag == 0) {                                            \
    void *ip_copy;                                              \
    ip_copy = &&FC_CONCAT(RESUME, __LINE__);	                \
      __asm__ __volatile__(                                     \
          ""                                                    \
          : "=z" (ip_copy)                                      \
          : "0" (ip_copy)                                       \
      );                                                        \
    (ip) = ip_copy;                                             \
    return;                                                     \
  }                                                             \
  FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));  \
} while(0)

#else


/**
* Yield control the current virtual thread.
* The value of instruction pointer is not changed.
* Once the virtual thread function is called again, it will execute form the same position as last time.
* \param thread  A virtual thread name
* \param ip      An instruction pointer of the virtual thread
*/
#define VT_REWIND(thread, ip)                                                               \
do {                                                                                        \
  vt_flag = 0;				                                                                \
  if(vt_flag == 0) {                                                                        \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(REWIND, __LINE__)));                            \
    return;                                                                                 \
  }                                                                                         \
} while(0)


#define VT_YIELD_WITH_MARK(thread, ip, mark)                                                \
do {                                                                                        \
  vt_flag = 0;				                                                                \
  mark:                                                                                     \
  if(vt_flag == 0) {                                                                        \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(YIELD_AND_RESUME_AT_, mark)));                  \
    (ip) = &&mark;	                                                                        \
    return;                                                                                 \
  }                                                                                         \
  FC_ASM_LABEL(FC_LABEL(thread, mark));                                                     \
} while(0)


#define VT_YIELD(thread, ip) VT_YIELD_WITH_MARK(thread, ip, FC_CONCAT(RESUME, __LINE__))


#define VT_YIELD_WITH_MARK_IF_TRUE_ELSE_REWIND(condition, thread, ip, mark)                 \
do {                                                                                        \
  vt_flag = 0;				                                                                \
  mark:                                                                                     \
  if(vt_flag == 0) {                                                                        \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(YIELD_REWIND_OR_RESUME_AT_, mark)));            \
    if ((condition)) {                                                                      \
      (ip) = &&mark;                                                                        \
    }                                                                                       \
    return;                                                                                 \
  }                                                                                         \
  FC_ASM_LABEL(FC_LABEL(thread, mark));                                                     \
} while(0)



#endif


/**
 * Program the current virtual thread to go to the specified mark.
 * Once the virtual thread function is called again, it will resume from the specified mark.
 * \param thread  A virtual thread name
 * \param ip      An instruction pointer of the virtual thread
 * \param mark    The name of the mark to proceed from
 */
#define VT_GOTO(thread, ip, mark)                                                           \
do {                                                                                        \
  FC_CONCAT(FC_CONCAT(GOTO_, mark), __LINE__):                                              \
  (void)&&FC_CONCAT(FC_CONCAT(GOTO_, mark), __LINE__);                                      \
  vt_flag = 0;				                                                                \
  if(vt_flag == 0) {                                                                        \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(YIELD_AND_RESUME_AT_, mark)));                  \
    (ip) = &&mark;                                                                          \
    return;                                                                                 \
  }                                                                                         \
} while(0)


// =============================================================================
// Specialized versions of macros, for writing vthread-enabled ISR.
// (Only because GCC can't inline functions with computed goto, even static)
//
// for a new thread function f, the following symbols must be defined:
// f__function_attrs:   possible values - ISR_NAKED and/or __attribute((signal))
// f__function_naked:   possible values - 0 or 1 to insert reti at the end of ISR
// f__yield_with_reti:  possible values - 0 or 1 to implement yield with reti
// =============================================================================

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define __VT_FUNC_ATTRS used, externally_visible
#else /* GCC < 4.1 */
#  define __VT_FUNC_ATTRS used
#endif

#ifdef __cplusplus
#  define VT_FUNC(f, ...)                                                                   \
    extern "C" void f (void) __attribute__ ((__VT_FUNC_ATTRS)) __VA_ARGS__;                 \
    void f (void)
#else
#  define VT_FUNC(f, ...)                                                                   \
    void f (void) __attribute__ ((__VT_FUNC_ATTRS)) __VA_ARGS__;                            \
    void f (void)
#endif


/**
 * Declare the end of a virtual thread.
 * \param thread A virtual thread name
 */
#define VT_END_S(thread)                                                                    \
  }                                                                                         \
  FC_ASM_LABEL(FC_LABEL(thread, END));                                                      \
END:                                                                                        \
  (void)vt_flag;                                                                            \
  if (FC_CONCAT(thread, __function_naked))                                                  \
    __asm__ __volatile__ ("reti"::);                                                        \
  break;\
} while(0)


/**
 * Yield control from the current virtual thread.
 * Once the virtual thread function is called again, it will resume from the following operator.
 * \param thread  A virtual thread name
 * \param ip      An instruction pointer of the virtual thread
 */
#ifdef VTHREADS__FAST_YIELD


#define VT_YIELD_WITH_MARK_S(thread, ip, mark)                                              \
do {                                                                                        \
  FC_CONCAT(YIELD, __LINE__):                                                               \
  (void)&&FC_CONCAT(YIELD, __LINE__);                                                       \
  if (FC_CONCAT(thread,__yield_with_reti) == 0 && FC_CONCAT(thread,__function_naked) == 0) {\
    vt_flag = 0;				                                                            \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME_, __LINE__)));                           \
    if(vt_flag == 0) {                                                                      \
      void *ip_copy;                                                                        \
      __asm__ __volatile__ (		                                                        \
        "ldi %A0, pm_lo8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        "ldi %B0, pm_hi8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        : "=z"(ip_copy)                                                                     \
      );					                                                                \
      (ip) = ip_copy;                                                                       \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD_, __LINE__)));                       \
      return;                                                                               \
    }                                                                                       \
  }                                                                                         \
  else {                                                                                    \
    if (FC_CONCAT(thread,__yield_with_reti != 0)) {                                         \
      void *ip_copy;                                                                        \
      __asm__ __volatile__ (		                                                        \
        "ldi %A0, pm_lo8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        "ldi %B0, pm_hi8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        : "=z"(ip_copy)                                                                     \
      );					                                                                \
      (ip) = ip_copy;                                                                       \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD__, __LINE__)));                      \
      __asm__ __volatile__ ("reti"::);                                                      \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME__, __LINE__)));                        \
    }                                                                                       \
    else {                                                                                  \
      vt_flag = 0;				                                                            \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));                          \
      if (vt_flag == 0) {                                                                   \
        FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));       \
        FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD, __LINE__)));                      \
        goto END;                                                                           \
      }                                                                                     \
    }                                                                                       \
  }                                                                                         \
} while(0)

#define VT_YIELD_S(thread, ip) VT_YIELD_WITH_MARK_S(thread, ip, FC_CONCAT(RESUME, __LINE__))

#else

#define VT_YIELD_S(thread, ip)                                                              \
do {                                                                                        \
  FC_CONCAT(YIELD, __LINE__):                                                               \
  (void)&&FC_CONCAT(YIELD, __LINE__);                                                       \
  if (FC_CONCAT(thread,__yield_with_reti) == 0 && FC_CONCAT(thread,__function_naked) == 0) {\
    vt_flag = 0;				                                                            \
    FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME_, __LINE__)));                           \
    if(vt_flag == 0) {                                                                      \
      FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL(thread, FC_CONCAT(RESUME_, __LINE__)));        \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD_, __LINE__)));                       \
      return;                                                                               \
    }                                                                                       \
  }                                                                                         \
  else {                                                                                    \
    if (FC_CONCAT(thread,__yield_with_reti != 0)) {                                         \
        FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));       \
      __asm__ __volatile__ ("reti"::);                                                      \
    }                                                                                       \
    else {                                                                                  \
      vt_flag = 0;				                                                            \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));                          \
      if (vt_flag == 0) {                                                                   \
        FC_ASM_LOAD_LABEL_ADDRESS(ip, FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));       \
        FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD, __LINE__)));                      \
        goto END;                                                                           \
      }                                                                                     \
    }                                                                                       \
  }                                                                                         \
  FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(RESUME, __LINE__)));                              \
} while(0)

#endif


#define VT_Z_YIELD_WITH_MARK_RETI(thread, ip, mark)                                              \
do {                                                                                        \
  FC_CONCAT(YIELD, mark):                                                               \
  (void)&&FC_CONCAT(YIELD, mark);                                                       \
      __asm__ __volatile__ (		                                                        \
        "ldi zl, pm_lo8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        "ldi zh, pm_hi8(" FC_LABEL(thread, mark) ")\n\t"	                                \
      );					                                                                \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD__, mark)));                      \
      __asm__ __volatile__ ("reti"::);                                                      \
      FC_ASM_LABEL(FC_LABEL(thread, mark));                        \
} while(0)


#define VT_Z_GOTO_RETI(thread, ip, mark)                                              \
do {                                                                                        \
  FC_CONCAT(YIELD, mark):                                                               \
  (void)&&FC_CONCAT(YIELD, mark);                                                       \
      __asm__ __volatile__ (		                                                        \
        "ldi zl, pm_lo8(" FC_LABEL(thread, mark) ")\n\t"	                                \
        "ldi zh, pm_hi8(" FC_LABEL(thread, mark) ")\n\t"	                                \
      );					                                                                \
      FC_ASM_LABEL(FC_LABEL(thread, FC_CONCAT(DO_YIELD__, mark)));                      \
      __asm__ __volatile__ ("reti"::);                                                      \
} while(0)


#define VT_FAST_YIELD_RETI(thread, ip) VT_FAST_YIELD_WITH_MARK_RETI(thread, ip, FC_CONCAT(RESUME, __LINE__))

#endif
