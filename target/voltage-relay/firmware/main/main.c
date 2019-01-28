// =============================================================================
// The device for protection against abnormal mains voltage - main module.
//
// The program continuously compares the measured mains voltage
// against the parameters 'voltage_min' and 'voltage_max'.
// If the voltage is outside of this range, the load is disconnected with relay.
// When the voltage returns back to the safe range, it waits 'on_delay' seconds
// and connects the load back.
//
// If 'on_delay' is 0, the device will not switch back on after voltage anomaly.
//
// User interface:
//
// Normally, the display shows the current voltage (voltage display mode).
// In this mode, the digits are not blinking.
// The load can be manually connected and disconnected with "+" and "-" buttons.
// When the LED is green, the voltage is within limits and load is connected.
// When the LED is blinking red, the voltage is off limits and load is disconnected.
// When the LED alternates between red and green, the voltage is within limits,
// and the load will be connected soon.
//
// The user can press and hold for 1 second the "SET" button
// to edit the parameters:
// - voltage_max: when the red LED is on
// - voltage_min: when the green LED is on
// - on_delay:    when the LED alternates between red and green
// - angle:       (the time instant at which the voltage is measured)
//                when the LED is off.
// Press "SET" to switch between the parameters edited,
// and finally to return the to voltage display mode.
//
// Impl note: moving state to registers should make the code smaller and faster,
// but some obscure bugs appeared when trying to do it.
// (Although registers were not used by the compiler.)
//
// Possible improvement: automatically return to voltage display mode
// from configuration mode if no button is pressed for the long time.
//
// Possible improvement: compile for hardware with no buzzer.
//
// Possible improvement: UART communications.
// =============================================================================

#include "cpu/avr/util/bcd.h"
#include "cpu/avr/util/mult16x16.h"
#include "cpu/avr/drivers/display/segment/glyphs.h"
#include "cpu/avr/drivers/display/segment/dynamic3_thread.h"
#include "cpu/avr/drivers/display/segment/number_renderer.h"

#include "buttons.h"
#include "buzzer.h"
#include "led_thread.h"
#include "relay.h"
#include "system_timer.h"
#include "voltmeter.h"
#include "zero_cross_detector.h"

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <util/delay.h>

// state value is also LED mode that is applied in Display Voltage mode
#define STATE__LOAD_ON          LED_THREAD__MODE__GREEN
#define STATE__LOAD_OFF         LED_THREAD__MODE__RED_BLACK
#define STATE__ON_DELAY         LED_THREAD__MODE__RED_GREEN
#define STATE__PERSISTENT_OFF   LED_THREAD__MODE__RED

#define MODE__DISPLAY_VOLTAGE   (0)
#define MODE__EDIT_VOLTAGE_MAX  (1)
#define MODE__EDIT_VOLTAGE_MIN  (2)
#define MODE__EDIT_ON_DELAY     (3)
#define MODE__EDIT_ANGLE        (4)
#define MODE__EDIT_BUZZER       (5)

#define is_voltage_display_mode() (!mode)



#if VOLTAGE_GAP < 0 || VOLTAGE_GAP > 32
#  error "VOLTAGE_GAP must be greater than 0 and less than 32"
#endif

#if VOLTAGE_MAX < 128 || VOLTAGE_MAX > 383
#  error "VOLTAGE_MAX must be greater than 128 and less than 384 (and within limits of hardware)"
#endif

#if VOLTAGE_MIN < 128 || VOLTAGE_MIN > 383
#  error "VOLTAGE_MIN must be greater than 128 and less than 384 (and within limits of hardware)"
#endif

#if VOLTAGE_MAX - VOLTAGE_MIN < VOLTAGE_GAP
#  error "VOLTAGE_MAX and VOLTAGE_NIN must be at least VOLTAGE_GAP volts apart"
#endif

#if EE_VOLTAGE_MAX < 128 || EE_VOLTAGE_MAX > 383
#  error "EE_VOLTAGE_MAX must be greater than 128 and less than 384 (and within limits of hardware)"
#endif

#if EE_VOLTAGE_MIN < 128 || EE_VOLTAGE_MIN > 383
#  error "EE_VOLTAGE_MIN must be greater than 128 and less than 384 (and within limits of hardware)"
#endif

#if EE_VOLTAGE_MAX > VOLTAGE_MAX
#  error "EE_VOLTAGE_MAX must not be greater than VOLTAGE_MAX"
#endif

#if EE_VOLTAGE_MIN > VOLTAGE_MIN
#  error "EE_VOLTAGE_MIN must not be less than VOLTAGE_MAX"
#endif

#if EE_VOLTAGE_MAX - EE_VOLTAGE_MIN < VOLTAGE_GAP
#  error "EE_VOLTAGE_MAX and EE_VOLTAGE_NIN must be at least VOLTAGE_GAP volts apart"
#endif

#if ANGLE_MAX < 1 || ANGLE_MAX > 255
#  error "ANGLE_MAX must be greater than 0 and less than 256"
#endif

#if ANGLE_MIN < 1 || ANGLE_MIN > 255
#  error "ANGLE_MIN must be greater than 0 and less than 256"
#endif

#if ANGLE_MIN > ANGLE_MAX
#  error "ANGLE_MIN must not be greater than ANGLE_MAX"
#endif

#if EE_ANGLE < ANGLE_MIN || EE_ANGLE > ANGLE_MAX
#  error "EE_ANGLE must be not less than ANGLE_MIN and not greater than ANGLE_MAX"
#endif



//#define time_to_turn_on GPIOR1
volatile uint8_t  time_to_turn_on;
//register uint8_t  time_to_turn_on asm("r14");


#ifdef ENABLE_VOLTAGE_AVERAGING
//register uint16_t voltage_integral asm("r6");
uint16_t voltage_integral;
#endif


//#define readings_count GPIOR2
//register int8_t   readings_count asm("r3");
volatile int8_t   readings_count;


volatile uint8_t  state;
//register uint8_t state asm("r16");

//register uint8_t  mode;
volatile uint8_t  mode           = MODE__DISPLAY_VOLTAGE;
//register uint8_t mode asm("r17");

// BCD representatin of voltage.
// Cached to avoid BCD conversion on every system tick.
//register uint16_t voltage_bcd asm("r4");
volatile uint16_t voltage_bcd;


//register uint16_t voltage_max   asm("r8");
uint16_t voltage_max;

//register uint16_t voltage_min   asm("r10");
uint16_t voltage_min;

//register uint8_t on_delay       asm("r12");
uint16_t on_delay;

//register uint8_t angle          asm("r13");
uint8_t angle;

uint8_t buzzer;


uint16_t t_voltage_max;
uint16_t t_voltage_min;
uint8_t  t_on_delay;
uint8_t  t_angle;
uint8_t  t_buzzer;

// =============================================================================
// Data in EEPROM.
// For voltages, signed voltage-256 value is stored.
// =============================================================================

uint8_t  EEMEM          ee_voltage_max	= (uint8_t)(EE_VOLTAGE_MAX - 256);
uint8_t  EEMEM          ee_voltage_min  = (uint8_t)(EE_VOLTAGE_MIN - 256);
uint8_t  EEMEM          ee_on_delay     = EE_ON_DELAY;
uint8_t  EEMEM          ee_angle        = EE_ANGLE;
uint8_t  EEMEM          ee_buzzer       = EE_BUZZER;


// =============================================================================
// Switching states
// =============================================================================

inline static void to_load_off_state(void) {                
    uint8_t new_state = STATE__LOAD_OFF;
    state = new_state;
    relay__on(); // Relay on = disconnect load
    if (is_voltage_display_mode()) led_thread__mode__set(new_state);
    if (buzzer) buzzer__start();
}

inline static void to_load_on_state(void) {                
    uint8_t new_state = STATE__LOAD_ON;
    state = new_state;
    relay__off(); // Relay off = reconnect load
    if (is_voltage_display_mode()) led_thread__mode__set(new_state);
}

inline static void to_persistent_off_state(void) {
    // Always invoked in Voltage Display mode.
    uint8_t new_state = STATE__PERSISTENT_OFF;
    state = new_state;
    led_thread__mode__set(new_state);
    relay__on(); // Relay on = disconnect load
    buzzer__stop();
}

inline static void to_on_delay_state(void) {
    uint8_t new_state = STATE__ON_DELAY;
    state = new_state;
    if (is_voltage_display_mode()) led_thread__mode__set(new_state);
    buzzer__stop();
}

// =============================================================================
// Reading parameters from EEPROM
// =============================================================================

inline static void model__init(void) {
   t_voltage_max  = voltage_max  = 256 + (int8_t)eeprom_read_byte(&ee_voltage_max);
   t_voltage_min  = voltage_min  = 256 + (int8_t)eeprom_read_byte(&ee_voltage_min);
   t_on_delay     = on_delay     = eeprom_read_byte(&ee_on_delay);
   t_angle        = angle        = eeprom_read_byte(&ee_angle);
   t_buzzer       = buzzer       = eeprom_read_byte(&ee_buzzer);

#ifdef ENABLE_VOLTAGE_MONITOR
   if (on_delay) {
       to_load_on_state(); // optimizable (relay is off, voltage display mode)
   }
   else {
       to_persistent_off_state();
   }
#else
   to_load_on_state();
#endif
}

// =============================================================================
// Writing parameters to EEPROM
// =============================================================================

inline static void write_voltage_max(void) {
    if (t_voltage_max != voltage_max) {
        eeprom_write_byte(&ee_voltage_max, (uint8_t)(t_voltage_max - 256));
        voltage_max = t_voltage_max;
    }
}

inline static void write_voltage_min(void) {
    if (t_voltage_min != voltage_min) {
        eeprom_write_byte(&ee_voltage_min, (uint8_t)(t_voltage_min - 256));
        voltage_min = t_voltage_min;
    }
}

inline static void write_on_delay(void) {
    if (t_on_delay != on_delay) {
        eeprom_write_byte(&ee_on_delay, t_on_delay);
        on_delay = t_on_delay;
    }
}

inline static void write_angle(void) {
    if (t_angle != angle) {
        eeprom_write_byte(&ee_angle, t_angle);
        angle = t_angle;
    }
}

inline static void write_buzzer(void) {
    if (t_buzzer != buzzer) {
        eeprom_write_byte(&ee_buzzer, t_buzzer);
        buzzer = t_buzzer;
    }
}

// =============================================================================
// Displaying voltage and parameters
// =============================================================================

inline static void numeric_display__set(const uint16_t number) {
    number_renderer__render(number, (uint8_t *)display_thread__segments);
}


inline static void numeric_display__set_bcd(const uint16_t number) {
    numeric_display__set(uint9_to_bcd(number));
}

// Can be run concurrently, so the displayed voltage can be wrong
// But the chance is very low,
// and in a second the displayed value is overwritten anyway.
inline static void display_voltage(void) {
    numeric_display__set(voltage_bcd);
}

inline static void display_voltage_max(void) {
    numeric_display__set_bcd(t_voltage_max);
}

inline static void display_voltage_min(void) {
    numeric_display__set_bcd(t_voltage_min);
}

inline static void display_on_delay(void) {
    // display message "OFF" if t_on_delay is 0
    if (t_on_delay) {
        uint16_t number = uint9_to_bcd(t_on_delay) << 4; // <<4 adds 0 at the end
        numeric_display__set(number);
    }
    else
        numeric_display__set(0x0FF);
}

inline static void display_angle(void) {
    numeric_display__set_bcd(t_angle);
}

inline static void display_buzzer(void) {
    // display message "On" or "OFF" 
    if (t_buzzer) {
       display_thread__segments[0] = DISPLAY_SEGMENT_GLYPH_EMPTY;
       display_thread__segments[1] = DISPLAY_SEGMENT_GLYPH_0;
       display_thread__segments[2] = DISPLAY_SEGMENT_GLYPH_n;
    }
    else {
       display_thread__segments[0] = DISPLAY_SEGMENT_GLYPH_0;
       display_thread__segments[1] = DISPLAY_SEGMENT_GLYPH_F;
       display_thread__segments[2] = DISPLAY_SEGMENT_GLYPH_F;
    }
}


// =============================================================================
// Switching UI modes
// =============================================================================

inline static void to_voltage_display_mode(void) {
    mode = MODE__DISPLAY_VOLTAGE;
    led_thread__mode__set(state);
    display_voltage();
    display_thread__blink__off();
}

inline static void to_edit_voltage_max_mode(void) {
    mode = MODE__EDIT_VOLTAGE_MAX;
    led_thread__set_red();
    display_voltage_max();
    display_thread__blink__on();
}

inline static void to_edit_voltage_min_mode(void) {
    mode = MODE__EDIT_VOLTAGE_MIN;
    led_thread__set_green();
    display_voltage_min();
    display_thread__blink__on(); // optimizable (blink is already on)
}

inline static void to_edit_on_delay_mode(void) {
    mode = MODE__EDIT_ON_DELAY;
    led_thread__mode__set(LED_THREAD__MODE__RED_GREEN);
    display_on_delay();
    display_thread__blink__on(); // optimizable (blink is already on)
}

inline static void to_edit_angle_mode(void) {
    mode = MODE__EDIT_ANGLE;
    led_thread__set_black();
    display_angle();
    display_thread__blink__on(); // optimizable (blink is already on)
}

inline static void to_edit_buzzer_mode(void) {
    mode = MODE__EDIT_BUZZER;
    led_thread__mode__set(LED_THREAD__MODE__RED_BLACK);
    display_buzzer();
    display_thread__blink__on(); // optimizable (blink is already on)
}


// =============================================================================
// UI Controller
// =============================================================================

inline static void ui_controller__init(void) {
    to_voltage_display_mode(); // optimizable (blink is off, etc.)
}


inline static void ui_controller__run(void) {
    switch (mode) {
    case MODE__DISPLAY_VOLTAGE:
#ifdef DEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS
        if (button1__was_just_pressed()) {
            zero_cross_detector__start();
        }
#endif
        if (button1__was_pressed() && buttons__delay_elapsed()) {
            to_edit_voltage_max_mode();
        }
        if (button2__was_just_pressed()) { // Manual turn off
            to_persistent_off_state();
        }
        if (button3__was_just_pressed()) { // Try to turn on manually
#ifdef ENABLE_VOLTAGE_MONITOR
            time_to_turn_on = 0; // after next voltage measurument, if it is ok, turn on.
            to_on_delay_state();    // optimizable (always in Display Voltage mode)
#else
            to_load_on_state();
#endif
        }
        break;
    case MODE__EDIT_VOLTAGE_MAX:
        if (button1__was_just_pressed()) {
            write_voltage_max();
            to_edit_voltage_min_mode();
        }
        else {
            if (button2__was_just_pressed_or_repeated() && (t_voltage_max > voltage_min + VOLTAGE_GAP)) {
                --t_voltage_max;
                display_thread__blink__off();
                display_voltage_max();
            }
            if (button3__was_just_pressed_or_repeated() && (t_voltage_max < VOLTAGE_MAX)) {
                ++t_voltage_max;
                display_thread__blink__off();
                display_voltage_max();
            }
            if (button2__was_just_released() | button3__was_just_released()) {
                display_thread__blink__on();
            }
        }
        break;
    case MODE__EDIT_VOLTAGE_MIN:
        if (button1__was_just_pressed()) {
            write_voltage_min();
            to_edit_on_delay_mode();
        }
        else {
            if (button2__was_just_pressed_or_repeated() && (t_voltage_min > VOLTAGE_MIN)) {
                --t_voltage_min;
                display_thread__blink__off();
                display_voltage_min();
            }
            if (button3__was_just_pressed_or_repeated() && (t_voltage_min < voltage_max - VOLTAGE_GAP)) {
                ++t_voltage_min;
                display_thread__blink__off();
                display_voltage_min();
            }
            if (button2__was_just_released() | button3__was_just_released()) {
                display_thread__blink__on();
            }
        }
        break;
    case MODE__EDIT_ON_DELAY:
        if (button1__was_just_pressed()) {
            write_on_delay();
            to_edit_angle_mode();
        }
        else {
            if (button2__was_just_pressed_or_repeated() && (t_on_delay > 0)) {
                --t_on_delay;
                display_thread__blink__off();
                display_on_delay();
            }
            if (button3__was_just_pressed_or_repeated() && (t_on_delay < 60)) {
                ++t_on_delay;
                display_thread__blink__off();
                display_on_delay();
            }
            if (button2__was_just_released() | button3__was_just_released()) {
                display_thread__blink__on();
            }
        }
        break;
    case MODE__EDIT_ANGLE:    
        if (button1__was_just_pressed()) {
            write_angle();
            to_edit_buzzer_mode();
        }
        else {
            if (button2__was_just_pressed_or_repeated() && (t_angle > ANGLE_MIN)) {
                --t_angle;
                display_thread__blink__off();
                display_angle();
            }
            if (button3__was_just_pressed_or_repeated() && (t_angle < ANGLE_MAX)) {
                ++t_angle;
                display_thread__blink__off();
                display_angle();
            }
            if (button2__was_just_released() | button3__was_just_released()) {
                display_thread__blink__on();
            }
        }
        break;
    case MODE__EDIT_BUZZER:    
        if (button1__was_just_pressed()) {
            write_buzzer();
            to_voltage_display_mode();
        }
        else {
            if (button2__was_just_pressed_or_repeated() && (t_buzzer > 0)) {
                t_buzzer = 0;
                display_buzzer();
            }
            if (button3__was_just_pressed_or_repeated() && (t_buzzer == 0)) {
                t_buzzer = 1;
                display_buzzer();
            }
        }
        break;
    }    
}


// =============================================================================
// Implementation of callbacks from other modules
// =============================================================================

INLINE void on_system_tick(void) {
    buttons__run();
    ui_controller__run();
    display_thread__run();
}

INLINE void on_phase_on(void) {
    led_thread__phase_on();
    display_thread__phase_on();
}

INLINE void on_phase_off(void) {
    led_thread__phase_off();
    display_thread__phase_off();
}

INLINE void on_second_tick(void) {
}

INLINE void on_ten_seconds_tick(void) {
    if (time_to_turn_on > 0) --time_to_turn_on;
}

INLINE void on_zero_cross(void) {
    voltmeter__delayed_run(angle << 8);
}

INLINE void update_voltage(const uint16_t value) {
    voltage_bcd = uint9_to_bcd(value);
    if (is_voltage_display_mode()) display_voltage();
}


INLINE void on_voltage_measured(uint16_t reading) {

/*
    voltage_integral += reading;

    // count from 64 to 0, then start over
    --counter;    
    if (counter < 0) {
        counter = 64;
        on_voltage_measured((voltage_integral * (VOLTAGE_MULTIPLIER/64)) >> 16);
        voltage_integral = 0;
    }
*/

    // voltage = reading * mult
    uint16_t mult = (uint16_t)VOLTAGE_MULTIPLIER;
    uint16_t voltage;
    MultiU16X16toH16(voltage, reading, mult);

#ifdef DEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS
    zero_cross_detector__stop();
    update_voltage(voltage);    
#endif

#ifdef ENABLE_VOLTAGE_MONITOR

    if (!(voltage < voltage_max && voltage > voltage_min)) {
//        debug__write('#');
        if (state != STATE__PERSISTENT_OFF) {
            if (on_delay != 0)
                to_load_off_state();
            else
                to_persistent_off_state();
        }
    }
    else { // voltage_ok
//        debug__write('.');
        if (state == STATE__LOAD_OFF) {
            to_on_delay_state();
            time_to_turn_on = on_delay;
        }
        else {
            if (state == STATE__ON_DELAY && time_to_turn_on == 0) {
                to_load_on_state();
            }
        }
        // no change in Persistent Off state and in Load On state
    }
#endif


#ifdef ENABLE_VOLTAGE_AVERAGING
    voltage_integral += voltage;
    --readings_count;    
    if (readings_count < 0) {
        readings_count = 64;
        update_voltage(voltage_integral >> 6);
        voltage_integral = 0;
    }
#endif
}


// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    _delay_ms(50);

//    uart_set_rate();
//    uart_setup();
//    uart_enable_tx();
//    uart_enable_rx();

    voltmeter__init();
    buttons__init();

    relay__init();
    buzzer__init();

    model__init();
    ui_controller__init();

    led_thread__init();
    display_thread__init();

    _delay_ms(200);

    system_timer__init();
    system_timer__start();
    sei();

    _delay_ms(50);

    zero_cross_detector__init();
#ifndef DEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS
    zero_cross_detector__start();
#endif

    sleep_enable(); // IDLE mode by default
    for(;;);
    return 0;
}
