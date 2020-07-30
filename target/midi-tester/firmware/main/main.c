// =============================================================================
// MIDI tester.
// Scans 4 buttons and sends MIDI NoteOn messages (using Soft USART).
//
// When button 0 is pressed, NoteOn C4, v=127 is sent; v=0 when released.
// When button 1 is pressed, NoteOn E4, v=127 is sent; v=0 when released.
// When button 2 is pressed, NoteOn G4, v=127 is sent; v=0 when released.
// When button 3 is pressed, NoteOn B4, v=127 is sent; v=0 when released.
//
// It is possible so select MIDI channel at power-on time by holding buttons.
// The combination determines the channel:
// 0000 (all buttons released) => channel 1
// ...
// 1111 (all butons pressed) => channel 16
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/services/keyboard/keyboard.h>
#include <cpu/avr/gpio.h>

#include "soft_usart__timer.h"
#include "soft_usart__tx__thread.h"
#include "soft_usart__tx.h"


void keyboard__port_b__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_b__debounce_timer__init(void) {}


uint8_t status_byte;

void read_config_from_buttons() {
    uint8_t port_value = PORT_VALUE(IN__BUTTONS);
    uint8_t b = 0x9F;   // note on, channel 16
    if (port_value & _BV(IN__BUTTON0__PIN)) b &= (0xFF - 1);
    if (port_value & _BV(IN__BUTTON1__PIN)) b &= (0xFF - 2);
    if (port_value & _BV(IN__BUTTON2__PIN)) b &= (0xFF - 4);
    if (port_value & _BV(IN__BUTTON3__PIN)) b &= (0xFF - 8);
    status_byte = b;
}

uint8_t button_to_midi_key(uint8_t button) {
    uint8_t key = 0;
    if (button == 0) key = 60;  // C4
    if (button == 1) key = 64;  // E4
    if (button == 2) key = 67;  // G4
    if (button == 3) key = 77;  // B4
    return key;
}

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-31)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */

bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    uint8_t key = button_to_midi_key(button);
    soft_usart__tx__write(status_byte);
    soft_usart__tx__write(key);
    soft_usart__tx__write((state & _BV(bit)) ? 0x00 : 0x7F);
    return true;
}


int main(void) {
    keyboard__init();
    _delay_ms(100);
    read_config_from_buttons();

    soft_usart__tx__pin__init();
    soft_usart__timer__init();

    sei();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    for(;;) {
        keyboard__run();
    }

#pragma clang diagnostic pop

    return 0;
}
