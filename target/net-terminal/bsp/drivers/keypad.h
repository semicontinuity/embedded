// =============================================================================
// Keypad driver.
// =============================================================================

#ifndef __DRIVERS__KEYPAD_H
#define __DRIVERS__KEYPAD_H

#include "cpu/avr/gpio.h"


#define KEYPAD__EVENT__MASK__PRESSED    (1<<7)
#define KEYPAD__EVENT__FLAG__PRESSED    (0<<7)
#define KEYPAD__EVENT__FLAG__RELEASED   (1<<7)

#define COL(col)		((col) << 2)
#define ROW(row)		((row) << 0)

#define KEYEVENT_D_PRESSED      (ROW(0) | COL(0))
#define KEYEVENT_C_PRESSED      (ROW(1) | COL(0))
#define KEYEVENT_B_PRESSED      (ROW(2) | COL(0))
#define KEYEVENT_A_PRESSED      (ROW(3) | COL(0))
#define KEYEVENT_STAR_PRESSED   (ROW(0) | COL(1))
#define KEYEVENT_7_PRESSED      (ROW(1) | COL(1))
#define KEYEVENT_4_PRESSED      (ROW(2) | COL(1))
#define KEYEVENT_1_PRESSED      (ROW(3) | COL(1))
#define KEYEVENT_0_PRESSED      (ROW(0) | COL(2))
#define KEYEVENT_8_PRESSED      (ROW(1) | COL(2))
#define KEYEVENT_5_PRESSED      (ROW(2) | COL(2))
#define KEYEVENT_2_PRESSED      (ROW(3) | COL(2))
#define KEYEVENT_POUND_PRESSED  (ROW(0) | COL(3))
#define KEYEVENT_9_PRESSED      (ROW(1) | COL(3))
#define KEYEVENT_6_PRESSED      (ROW(2) | COL(3))
#define KEYEVENT_3_PRESSED      (ROW(3) | COL(3))

#define KEYEVENT_D_RELEASED     (ROW(0) | COL(0) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_C_RELEASED     (ROW(1) | COL(0) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_B_RELEASED     (ROW(2) | COL(0) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_A_RELEASED     (ROW(3) | COL(0) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_STAR_RELEASED  (ROW(0) | COL(1) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_7_RELEASED     (ROW(1) | COL(1) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_4_RELEASED     (ROW(2) | COL(1) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_1_RELEASED     (ROW(3) | COL(1) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_0_RELEASED     (ROW(0) | COL(2) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_8_RELEASED     (ROW(1) | COL(2) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_5_RELEASED     (ROW(2) | COL(2) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_2_RELEASED     (ROW(3) | COL(2) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_POUND_RELEASED (ROW(0) | COL(3) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_9_RELEASED     (ROW(1) | COL(3) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_6_RELEASED     (ROW(2) | COL(3) | KEYPAD__EVENT__FLAG__RELEASED)
#define KEYEVENT_3_RELEASED     (ROW(3) | COL(3) | KEYPAD__EVENT__FLAG__RELEASED)


inline void keypad__init(void) {
    DATA_DIR_REG(KEYPAD__OUT__PORT) |= ((1<<(KEYPAD__OUT__PIN+3)) | (1<<(KEYPAD__OUT__PIN+2)) | (1<<(KEYPAD__OUT__PIN+1)) | (1<<(KEYPAD__OUT__PIN+0)));
    PORT_REG(KEYPAD__IN__PORT) |= ((1<<(KEYPAD__IN__PIN+3)) | (1<<(KEYPAD__IN__PIN+2)) | (1<<(KEYPAD__IN__PIN+1)) | (1<<(KEYPAD__IN__PIN+0)));
}

INLINE void keypad__run(void);

/** An application must define this event handler */
void keypad__on_event(uint8_t keyevent) __attribute__((noinline));


#endif